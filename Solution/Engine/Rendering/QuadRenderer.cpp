#include "stdafx.h"

#include "AssetContainer.h"
#include <d3dx11effect.h>
#include "QuadRenderer.h"
#include "GPUContext.h"
#include "GPUData.h"
#include "Effect.h"

#include "Renderer.h"
#include "Camera.h"


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
	}


	QuadRenderer::~QuadRenderer()
	{
	}

	void QuadRenderer::AddSpriteCommand(Texture* aTexture, const CU::Matrix44<float>& aOrientation
		, const CU::Vector4<float>& aSizeAndHotSpot, const CU::Vector4<float>& aPositionAndScale)
	{
		mySpriteCommands.Add(SpriteCommand(aTexture, aOrientation, aSizeAndHotSpot, aPositionAndScale));
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
		aRenderer.SetMatrix("Projection", aCamera.GetOrthagonalProjection());

		for each (SpriteCommand command in mySpriteCommands)
		{
			aRenderer.SetMatrix("SpriteOrientation", command.myOrientation);
			aRenderer.SetVector("SpriteSizeAndHotSpot", command.mySizeAndHotSpot);
			aRenderer.SetVector("SpritePositionAndScale", command.myPositionAndScale);
			aRenderer.SetTexture("AlbedoTexture", command.myTexture);

			Render(mySpriteEffect, "Render");
		}

		mySpriteCommands.RemoveAll();
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

}