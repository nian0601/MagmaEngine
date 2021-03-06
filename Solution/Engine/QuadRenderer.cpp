#include "stdafx.h"

#include "AssetContainer.h"
#include <d3dx11effect.h>
#include "QuadRenderer.h"
#include "GPUContext.h"
#include "GPUData.h"
#include "Effect.h"

#include "Renderer.h"
#include "Camera.h"

#include "TextData.h"
#include "Font.h"
#include "..\CommonUtilities\MathHelper.h"

namespace Magma
{
	QuadRenderer::QuadRenderer(AssetContainer& aAssetContainer, GPUContext& aGPUContext)
		: myAssetContainer(aAssetContainer)
		, myGPUContext(aGPUContext)
		, mySpriteCommands(128)
	{
		CU::GrowingArray<VertexPosUV> vertices(4);
		vertices.Add({ { -1.f, -1.f, 0.f }, { 0.f, 1.f } }); //topleft
		vertices.Add({ { 1.f, -1.f, 0.f }, { 1.f, 1.f } }); //topright
		vertices.Add({ { -1.f, 1.f, 0.f }, { 0.f, 0.f } }); //bottomleft
		vertices.Add({ { 1.f, 1.f, 0.f }, { 1.f, 0.f } }); //bottomright


		CU::GrowingArray<int> indices(6);
		indices.Add(0);
		indices.Add(2);
		indices.Add(1);

		indices.Add(1);
		indices.Add(2);
		indices.Add(3);


		myGPUData.SetTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
		myGPUData.AddInputElement(new D3D11_INPUT_ELEMENT_DESC({ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 }));
		myGPUData.AddInputElement(new D3D11_INPUT_ELEMENT_DESC({ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 }));
		myGPUData.Init(aAssetContainer.LoadEffect("Data/Resource/Shader/S_effect_fullscreen.fx")
			, indices.Size(), reinterpret_cast<char*>(&indices[0]), vertices.Size()
			, sizeof(VertexPosUV), reinterpret_cast<char*>(&vertices[0]), myGPUContext, myAssetContainer);

		mySpriteEffect = myAssetContainer.LoadEffect("Data/Resource/Shader/S_effect_sprite.fx");

		myProjectionVariable = myAssetContainer.CreateEffectVariableID("Projection");
		myOrientationVariable = myAssetContainer.CreateEffectVariableID("Orientation");
		mySizeAndHotSpotVariable = myAssetContainer.CreateEffectVariableID("SizeAndHotSpot");
		myPosAndScaleVarible = myAssetContainer.CreateEffectVariableID("PositionAndScale");
		myAlbedoTextureVariable = myAssetContainer.CreateEffectVariableID("AlbedoTexture");

		myFont = myAssetContainer.LoadFont("Data/Resource/Font/Font.png");
		myFontEffect = myAssetContainer.LoadEffect("Data/Resource/Shader/S_effect_font.fx");
		myTextData.Init(myFontEffect, myGPUContext, myAssetContainer);
	}


	QuadRenderer::~QuadRenderer()
	{
	}

	void QuadRenderer::AddSpriteCommand(Texture* aTexture, const CU::Matrix44<float>& aOrientation
		, const CU::Vector4<float>& aSizeAndHotSpot, const CU::Vector4<float>& aPositionAndScale)
	{
		CU::Vector4<float> flippedPosAndScale(aPositionAndScale);
		flippedPosAndScale.y *= -1.f;

		mySpriteCommands.Add(SpriteCommand(aTexture, aOrientation, aSizeAndHotSpot, flippedPosAndScale));
	}

	void QuadRenderer::AddTextCommand(const CU::String& aString, const CU::Vector2<float>& aPosition)
	{
		myTextCommands.Add(TextCommand(myFont, aString, aPosition));
	}

	void QuadRenderer::AddTextCommand(Font* aFont, const CU::String& aString, const CU::Vector2<float>& aPosition)
	{
		myTextCommands.Add(TextCommand(aFont, aString, aPosition));
	}

	void QuadRenderer::Activate()
	{
		const unsigned int byteOffset = 0;
		ID3D11DeviceContext* context = myGPUContext.GetContext();
		const IndexBuffer& indexBuffer = myGPUData.GetIndexBuffer();
		const VertexBuffer& vertexBuffer = myGPUData.GetVertexBuffer();

		context->IASetInputLayout(myGPUData.GetInputLayout());
		context->IASetIndexBuffer(indexBuffer.myIndexBuffer, DXGI_FORMAT(indexBuffer.myIndexBufferFormat), byteOffset);
		context->IASetVertexBuffers(0, 1, &vertexBuffer.myVertexBuffer, &vertexBuffer.myStride, &byteOffset);
		context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY(myGPUData.GetTopology()));
	}

	void QuadRenderer::RenderSprites(const Camera& aCamera, Renderer& aRenderer)
	{
		Activate();
		aRenderer.SetEffect(mySpriteEffect);
		aRenderer.SetMatrix(myProjectionVariable, aCamera.GetOrthagonalProjection());

		for each (SpriteCommand command in mySpriteCommands)
		{
			aRenderer.SetMatrix(myOrientationVariable, command.myOrientation);
			aRenderer.SetVector(mySizeAndHotSpotVariable, command.mySizeAndHotSpot);
			aRenderer.SetVector(myPosAndScaleVarible, command.myPositionAndScale);
			aRenderer.SetTexture(myAlbedoTextureVariable, command.myTexture);

			Render(mySpriteEffect, "Render");
		}

		mySpriteCommands.RemoveAll();
	}

	void QuadRenderer::RenderTexts(const Camera& aCamera, Renderer& aRenderer)
	{
		CU::Vector4<float> posAndScale(1.f, 1.f, 1.f, 1.f);
		
		for (const TextCommand& text : myTextCommands)
		{
			posAndScale.x = text.myPosition.x;
			posAndScale.y = -text.myPosition.y;
			posAndScale.z = text.myFont->GetScale();
			posAndScale.w = text.myFont->GetScale();

			CU::Math::Round(posAndScale.x);
			CU::Math::Round(posAndScale.y);

			myTextData.SetupBuffers(text.myString, text.myFont);
			RenderText(&myTextData, aCamera, aRenderer, posAndScale);
		}

		myTextCommands.RemoveAll();
	}

	void QuadRenderer::Render(EffectID aEffect, const CU::String& aTechnique)
	{
		ID3D11DeviceContext* context = myGPUContext.GetContext();
		Effect* effect = myAssetContainer.GetEffect(aEffect);

		D3DX11_TECHNIQUE_DESC techDesc;
		effect->GetTechnique(aTechnique)->GetDesc(&techDesc);
		for (UINT i = 0; i < techDesc.Passes; ++i)
		{
			effect->GetTechnique(aTechnique)->GetPassByIndex(i)->Apply(0, context);
			context->DrawIndexed(6, 0, 0);
		}
	}

	void QuadRenderer::RenderText(TextData* someTextData, const Camera& aCamera, Renderer& aRenderer, const CU::Vector4<float>& aPositionAndScale)
	{
		Activate();
		aRenderer.SetEffect(someTextData->GetEffectID());
		aRenderer.SetMatrix(myProjectionVariable, aCamera.GetOrthagonalProjection());
		aRenderer.SetVector(myPosAndScaleVarible, aPositionAndScale);

		aRenderer.SetTexture(myAlbedoTextureVariable, someTextData->GetFont()->GetTexture());

		aRenderer.SetBlendState(ALPHA_BLEND);
		aRenderer.RenderGPUData(*someTextData->GetGPUData());
		aRenderer.SetBlendState(NO_BLEND);
	}

	float QuadRenderer::GetTextHeight() const
	{
		return myFont->GetMaxHeight();
	}

}