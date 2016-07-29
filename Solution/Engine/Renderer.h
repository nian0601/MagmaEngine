#pragma once

#include "Backbuffer.h"
#include <CUMap.h>
#include <CUString.h>
#include "FullscreenQuad.h"
#include <Matrix.h>
#include "ModelData.h"
#include <Vector.h>
#include <Subscriber.h>
#include <GrowingArray.h>
#include <RenderMessage.h>

struct ID3DX11EffectVariable;
struct ID3D11RenderTargetView;
struct ID3D11DepthStencilView;
struct ID3D11RasterizerState;
struct ID3D11DepthStencilState;

namespace Easy3D
{
	class AssetContainer;
	class Camera;
	class Effect;
	class GPUContext;
	class Texture;

	enum eDepthState
	{
		ENABLED,
		DISABLED,
		READ_NO_WRITE,
		NO_READ_NO_WRITE,
		_DEPTH_COUNT
	};

	enum eRasterizer
	{
		CULL_BACK,
		WIRE_FRAME,
		NO_CULLING,
		_RAZTER_COUNT
	};

	class Renderer : public FullscreenQuad, public Subscriber
	{
	public:
		Renderer(EffectID aFullscreenEffect, AssetContainer& aAssetContainer, GPUContext& aGPUContext);
		~Renderer();

		void ReceiveMessage(const RenderMessage& aMessage) override;
		void RenderModels(const Camera& aCamera);

		void SetEffect(EffectID aEffect);
		void SetTexture(const CU::String<64>& aName, Texture* aTexture);
		void SetMatrix(const CU::String<64>& aName, const CU::Matrix44<float>& aMatrix);
		void SetVector(const CU::String<64>& aName, const CU::Vector3<float>& aVector);
		void SetVector(const CU::String<64>& aName, const CU::Vector4<float>& aVector);
		void SetRawData(const CU::String<64>& aName, int aDataSize, const void* someData);

		void SetClearColor(const CU::Vector4<float>& aColor);

		void SetRasterizerState(eRasterizer aState);
		void SetDepthStencilState(eDepthState aState);

		void AddRenderTarget(Texture* aTexture);
		void ClearRenderTarget(Texture* aTexture);
		void SetDepthStencil(Texture* aTexture);
		void ClearDepthStencil(Texture* aTexture);
		void UseOriginalDepthStencil();
		void UseOriginalRenderTarget();
		void ApplyRenderTargetAndDepthStencil();

		void RenderFullScreen(const CU::String<30>& aTechnique);
		void RenderModel(ModelID aModelID);

	private:
		ID3DX11EffectVariable* GetEffectVariable(const CU::String<64>& aName);
		void RenderModelData(const ModelData& someData);
		void RenderGPUData(const GPUData& someData);

		void CreateRasterizerStates();
		void CreateDepthStencilStates();

		EffectID myCurrentEffect;
		float myClearColor[4];

		int myRenderTargetCount;
		ID3D11RenderTargetView* myRenderTargets[4];
		ID3D11DepthStencilView* myDepthStencil;
		Backbuffer myBackbuffer;
		GPUContext& myGPUContext;

		CU::Map<EffectID, CU::Map<CU::String<64>, ID3DX11EffectVariable*>> myEffectVariables;

		ID3D11RasterizerState* myRasterizerStates[static_cast<int>(eRasterizer::_RAZTER_COUNT)];
		ID3D11DepthStencilState* myDepthStencilStates[static_cast<int>(eDepthState::_DEPTH_COUNT)];

		CU::GrowingArray<RenderMessage> myRenderBuffer;
		AssetContainer& myAssetContainer;
	};
}