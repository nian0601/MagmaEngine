#include "stdafx.h"

#include "AssetContainer.h"
#include <d3dx11effect.h>
#include <d3d11.h>
#include "Effect.h"
#include "GfxStructs.h"
#include "GPUContext.h"
#include "GPUData.h"


namespace Magma
{
	GPUData::GPUData()
		: myShaderResourceNames(8)
		, myTextures(8)
		, myVertexFormat(8)
		, myVertexBuffer(nullptr)
		, myVertexData(nullptr)
		, myIndexBuffer(nullptr)
		, myIndexData(nullptr)
	{
	}


	GPUData::~GPUData()
	{
		SAFE_DELETE(myIndexData);
		SAFE_DELETE(myVertexData);

		if (myVertexBuffer != nullptr && myVertexBuffer->myVertexBuffer != nullptr)
		{
			myVertexBuffer->myVertexBuffer->Release();
			delete myVertexBuffer;
		}

		if (myIndexBuffer != nullptr && myIndexBuffer->myIndexBuffer != nullptr)
		{
			myIndexBuffer->myIndexBuffer->Release();
			delete myIndexBuffer;
		}

		myVertexFormat.DeleteAll();
	}

	void GPUData::Init(EffectID aEffect, GPUContext& aGPUContext, AssetContainer& aAssetContainer)
	{
		const int size = myVertexFormat.Size();
		D3D11_INPUT_ELEMENT_DESC* vertexDesc = new D3D11_INPUT_ELEMENT_DESC[size];
		for (int i = 0; i < myVertexFormat.Size(); ++i)
		{
			vertexDesc[i] = *myVertexFormat[i];
		}

		InitInputLayout(vertexDesc, size, aEffect, aGPUContext, aAssetContainer);
		delete[] vertexDesc;

		InitVertexBuffer(myVertexData->myStride, D3D11_USAGE_IMMUTABLE, 0);
		InitIndexBuffer();

		SetupVertexBuffer(myVertexData->myNumberOfVertices, myVertexData->myVertexData, aGPUContext);
		SetupIndexBuffer(myIndexData->myNumberOfIndices, myIndexData->myIndexData, aGPUContext);

		myTechniqueName = "Render";
	}

	void GPUData::Init(EffectID aEffect, int aIndexCount, char* aIndexData
		, int aVertexCount, int aVertexStride, char* aVertexData, GPUContext& aGPUContext, AssetContainer& aAssetContainer)
	{
		const int size = myVertexFormat.Size();
		D3D11_INPUT_ELEMENT_DESC* vertexDesc = new D3D11_INPUT_ELEMENT_DESC[size];
		for (int i = 0; i < myVertexFormat.Size(); ++i)
		{
			vertexDesc[i] = *myVertexFormat[i];
		}

		InitInputLayout(vertexDesc, size, aEffect, aGPUContext, aAssetContainer);
		delete[] vertexDesc;

		InitVertexBuffer(aVertexStride, D3D11_USAGE_IMMUTABLE, 0);
		InitIndexBuffer();

		SetupIndexBuffer(aIndexCount, aIndexData, aGPUContext);
		SetupVertexBuffer(aVertexCount, aVertexData, aGPUContext);

		myTechniqueName = "Render";
	}

	void GPUData::InitCube(EffectID aEffect, GPUContext& aGPUContext, AssetContainer& aAssetContainer)
	{
#pragma region Vertices
		CU::GrowingArray<VertexPosColor> vertices;
		vertices.Init(24);

		float size = 10.f;
		float halfWidth = size / 2.f;
		float halfHeight = size / 2.f;
		float halfDepth = size / 2.f;
		CU::Vector4<float> aColour(1.f, 1.f, 1.f, 1.f);

		//0 - 3 (Top)
		vertices.Add({ { -halfWidth, halfHeight, -halfDepth }, aColour });
		vertices.Add({ { halfWidth, halfHeight, -halfDepth }, aColour });
		vertices.Add({ { halfWidth, halfHeight, halfDepth }, aColour });
		vertices.Add({ { -halfWidth, halfHeight, halfDepth }, aColour });

		//4 - 7 (Bottom)
		vertices.Add({ { -halfWidth, -halfHeight, -halfDepth }, aColour });
		vertices.Add({ { halfWidth, -halfHeight, -halfDepth }, aColour });
		vertices.Add({ { halfWidth, -halfHeight, halfDepth }, aColour });
		vertices.Add({ { -halfWidth, -halfHeight, halfDepth }, aColour });

		//8 - 11 (Left)
		vertices.Add({ { -halfWidth, -halfHeight, halfDepth }, aColour });
		vertices.Add({ { -halfWidth, -halfHeight, -halfDepth }, aColour });
		vertices.Add({ { -halfWidth, halfHeight, -halfDepth }, aColour });
		vertices.Add({ { -halfWidth, halfHeight, halfDepth }, aColour });

		//12 - 15 (Right)
		vertices.Add({ { halfWidth, -halfHeight, halfDepth }, aColour });
		vertices.Add({ { halfWidth, -halfHeight, -halfDepth }, aColour });
		vertices.Add({ { halfWidth, halfHeight, -halfDepth }, aColour });
		vertices.Add({ { halfWidth, halfHeight, halfDepth }, aColour });

		//16 - 19 (Front)
		vertices.Add({ { -halfWidth, -halfHeight, -halfDepth }, aColour });
		vertices.Add({ { halfWidth, -halfHeight, -halfDepth }, aColour });
		vertices.Add({ { halfWidth, halfHeight, -halfDepth }, aColour });
		vertices.Add({ { -halfWidth, halfHeight, -halfDepth }, aColour });

		//20 - 23 (Back)
		vertices.Add({ { -halfWidth, -halfHeight, halfDepth }, aColour });
		vertices.Add({ { halfWidth, -halfHeight, halfDepth }, aColour });
		vertices.Add({ { halfWidth, halfHeight, halfDepth }, aColour });
		vertices.Add({ { -halfWidth, halfHeight, halfDepth }, aColour });
#pragma endregion

#pragma region Indices

		CU::GrowingArray<int> indices(24);
		//Top
		indices.Add(3);
		indices.Add(1);
		indices.Add(0);

		indices.Add(2);
		indices.Add(1);
		indices.Add(3);

		//Bottom
		indices.Add(6);
		indices.Add(4);
		indices.Add(5);

		indices.Add(7);
		indices.Add(4);
		indices.Add(6);

		//Left
		indices.Add(11);
		indices.Add(9);
		indices.Add(8);

		indices.Add(10);
		indices.Add(9);
		indices.Add(11);

		//Right
		indices.Add(14);
		indices.Add(12);
		indices.Add(13);

		indices.Add(15);
		indices.Add(12);
		indices.Add(14);

		//Front
		indices.Add(19);
		indices.Add(17);
		indices.Add(16);

		indices.Add(18);
		indices.Add(17);
		indices.Add(19);

		//Back
		indices.Add(22);
		indices.Add(20);
		indices.Add(21);

		indices.Add(23);
		indices.Add(20);
		indices.Add(22);

#pragma endregion

		SetTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
		AddInputElement(new D3D11_INPUT_ELEMENT_DESC({ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 }));
		AddInputElement(new D3D11_INPUT_ELEMENT_DESC({ "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 }));

		int indexCount = indices.Size();
		int vertexCount = vertices.Size();
		int vertexStride = sizeof(VertexPosColor);
		Init(aEffect, indexCount, reinterpret_cast<char*>(&indices[0]), vertexCount
			, vertexStride, reinterpret_cast<char*>(&vertices[0]), aGPUContext, aAssetContainer);

		myIndexData = new IndexData();
		myVertexData = new VertexData();

		myIndexData->myNumberOfIndices = indexCount;
		myVertexData->myNumberOfVertices = vertexCount;
		myVertexData->myStride = vertexStride;
	}

	void GPUData::InitWithoutBufferSetup(EffectID aEffect, int aVertexStride, GPUContext& aGPUContext, AssetContainer& aAssetContainer)
	{
		const int size = myVertexFormat.Size();
		D3D11_INPUT_ELEMENT_DESC* vertexDesc = new D3D11_INPUT_ELEMENT_DESC[size];
		for (int i = 0; i < myVertexFormat.Size(); ++i)
		{
			vertexDesc[i] = *myVertexFormat[i];
		}

		InitInputLayout(vertexDesc, size, aEffect, aGPUContext, aAssetContainer);
		delete[] vertexDesc;

		InitVertexBuffer(aVertexStride, D3D11_USAGE_IMMUTABLE, 0);
		InitIndexBuffer();

		myIndexData = new IndexData();
		myVertexData = new VertexData();
		SetTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

		myTechniqueName = "Render";
	}

	void GPUData::SetTopology(int aTopology)
	{
		myPrimitiveTopology = aTopology;
	}

	void GPUData::AddInputElement(D3D11_INPUT_ELEMENT_DESC* aElement)
	{
		myVertexFormat.Add(aElement);
	}

	void GPUData::UpdateBuffers(int aIndexCount, char* aIndexData, int aVertexCount, int aVertexStride, char* aVertexData, GPUContext& aGPUContext)
	{
		SetupIndexBuffer(aIndexCount, aIndexData, aGPUContext);
		SetupVertexBuffer(aVertexCount, aVertexData, aGPUContext);

		myIndexData->myNumberOfIndices = aIndexCount;
		myVertexData->myNumberOfVertices = aVertexCount;
		myVertexData->myStride = aVertexStride;
	}

	void GPUData::InitInputLayout(D3D11_INPUT_ELEMENT_DESC* aVertexDescArray, int aArraySize, EffectID aEffect, GPUContext& aGPUContext, AssetContainer& aAssetContainer)
	{
		Effect* effect = aAssetContainer.GetEffect(aEffect);

		D3DX11_PASS_DESC passDesc;
		effect->GetTechnique("Render")->GetPassByIndex(0)->GetDesc(&passDesc);
		HRESULT hr = aGPUContext.GetDevice()->CreateInputLayout(aVertexDescArray
			, aArraySize, passDesc.pIAInputSignature, passDesc.IAInputSignatureSize, &myInputLayout);
		if (FAILED(hr) != S_OK)
		{
			DL_MESSAGE_BOX("Failed to CreateInputLayout", "GPUData::Init", MB_ICONWARNING);
		}
	}

	void GPUData::InitVertexBuffer(int aVertexSize, int aBufferUsage, int aCPUUsage)
	{
		myVertexBuffer = new VertexBuffer();
		myVertexBuffer->myStride = aVertexSize;

		myVertexBuffer->myBufferDesc = new D3D11_BUFFER_DESC();
		ZeroMemory(myVertexBuffer->myBufferDesc, sizeof(*myVertexBuffer->myBufferDesc));
		myVertexBuffer->myBufferDesc->Usage = D3D11_USAGE(aBufferUsage);
		myVertexBuffer->myBufferDesc->BindFlags = D3D11_BIND_VERTEX_BUFFER;
		myVertexBuffer->myBufferDesc->CPUAccessFlags = aCPUUsage;
		myVertexBuffer->myBufferDesc->MiscFlags = 0;
		myVertexBuffer->myBufferDesc->StructureByteStride = 0;
	}

	void GPUData::InitIndexBuffer()
	{
		myIndexBuffer = new IndexBuffer();
		myIndexBuffer->myIndexBufferFormat = DXGI_FORMAT_R32_UINT;

		myIndexBuffer->myBufferDesc = new D3D11_BUFFER_DESC();
		ZeroMemory(myIndexBuffer->myBufferDesc, sizeof(*myIndexBuffer->myBufferDesc));
		myIndexBuffer->myBufferDesc->Usage = D3D11_USAGE_IMMUTABLE;
		myIndexBuffer->myBufferDesc->BindFlags = D3D11_BIND_INDEX_BUFFER;
		myIndexBuffer->myBufferDesc->CPUAccessFlags = 0;
		myIndexBuffer->myBufferDesc->MiscFlags = 0;
		myIndexBuffer->myBufferDesc->StructureByteStride = 0;
	}

	void GPUData::SetupVertexBuffer(int aVertexCount, char* aVertexData, GPUContext& aGPUContext)
	{
		if (myVertexBuffer->myVertexBuffer != nullptr)
		{
			SAFE_RELEASE(myVertexBuffer->myVertexBuffer);
		}

		myVertexBuffer->myBufferDesc->ByteWidth = myVertexBuffer->myStride * aVertexCount;
		D3D11_SUBRESOURCE_DATA initData;
		initData.pSysMem = aVertexData;

		DL_ASSERT_EXP(SUCCEEDED(aGPUContext.GetDevice()->CreateBuffer(myVertexBuffer->myBufferDesc, &initData
			, &myVertexBuffer->myVertexBuffer)) == TRUE, "GPUData::SetupVertexBuffer: Failed to SetupVertexBuffer");
	}

	void GPUData::SetupIndexBuffer(int aIndexCount, char* aIndexData, GPUContext& aGPUContext)
	{
		if (myIndexBuffer->myIndexBuffer != nullptr)
		{
			SAFE_RELEASE(myIndexBuffer->myIndexBuffer);
		}

		myIndexBuffer->myBufferDesc->ByteWidth = sizeof(UINT) * aIndexCount;
		D3D11_SUBRESOURCE_DATA initData;
		initData.pSysMem = aIndexData;

		DL_ASSERT_EXP(SUCCEEDED(aGPUContext.GetDevice()->CreateBuffer(myIndexBuffer->myBufferDesc, &initData,
			&myIndexBuffer->myIndexBuffer)) == TRUE, "GPUData::SetupIndexBuffer: Failed to SetupIndexBuffer");
	}

}