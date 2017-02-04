#include "stdafx.h"
#include "TextData.h"
#include "GPUData.h"
#include "Font.h"

#include <d3dx11effect.h>
#include "GfxStructs.h"

namespace Magma
{

	TextData::TextData()
	{

	}

	TextData::~TextData()
	{
		SAFE_DELETE(myGPUData);
	}

	void TextData::Init(EffectID aEffectID, GPUContext& aGPUContext, AssetContainer& aAssetContainer)
	{
		myGPUContext = &aGPUContext;

		myGPUData = new GPUData();
		myGPUData->AddInputElement(new D3D11_INPUT_ELEMENT_DESC({ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 }));
		myGPUData->AddInputElement(new D3D11_INPUT_ELEMENT_DESC({ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 }));

		myGPUData->InitWithoutBufferSetup(aEffectID, sizeof(VertexPosUV), aGPUContext, aAssetContainer);

		myEffectID = aEffectID;

	}

	void TextData::SetupBuffers(const CU::String& aString, Font* aFont)
	{
		myFont = aFont;

		int numOfLetters = aString.Size()+1;
		float drawX = 0;
		float drawY = 0;
		float z = 1.f;

		CU::GrowingArray<VertexPosUV> vertices(16);
		CU::GrowingArray<int> indices(16);

		VertexPosUV vert;
		for (int i = 0; i < numOfLetters; ++i)
		{
			CharData charData = aFont->GetCharData(aString[i]);

			float left = drawX + charData.myXOffset;
			float right = left + charData.myWidth;
			float top = drawY + charData.myYOffset;
			float bottom = top - charData.myHeight;


			vert.myPos = CU::Vector3<float>(left, top, z);
			vert.myUV = charData.myTopLeftUV;
			vertices.Add(vert);

			vert.myPos = CU::Vector3<float>(right, bottom, z);
			vert.myUV = charData.myBottomRightUV;
			vertices.Add(vert);

			vert.myPos = CU::Vector3<float>(left, bottom, z);
			vert.myUV = { charData.myTopLeftUV.x, charData.myBottomRightUV.y };
			vertices.Add(vert);

			vert.myPos = CU::Vector3<float>(right, top, z);
			vert.myUV = { charData.myBottomRightUV.x, charData.myTopLeftUV.y };
			vertices.Add(vert);


			int startIndex = i * 4;
			indices.Add(startIndex + 0);
			indices.Add(startIndex + 1);
			indices.Add(startIndex + 2);

			indices.Add(startIndex + 0);
			indices.Add(startIndex + 3);
			indices.Add(startIndex + 1);


			drawX += charData.myXAdvance;
			z -= 0.001f;
		}

		myGPUData->UpdateBuffers(indices.Size(), reinterpret_cast<char*>(&indices[0])
			, vertices.Size(), sizeof(VertexPosUV), reinterpret_cast<char*>(&vertices[0])
			, *myGPUContext);
	}
}