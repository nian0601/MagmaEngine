#pragma once

#include "IGPUFactory.h"

struct ID3DX11EffectVariable;
struct ID3D11RenderTargetView;
struct ID3D11DepthStencilView;
struct ID3D11RasterizerState;
struct ID3D11DepthStencilState;
struct ID3D11BlendState;

namespace Magma
{
	class DirectX;
	class DirectXFactory : public IGPUFactory
	{
	public:
		DirectXFactory(DirectX& anDirectX);
		~DirectXFactory();

		void SetRasterizerState(eRasterizer anRasterizerState) override;
		void SetDepthStencilState(eDepthState anDepthStencilState) override;
		void SetBlendState(eBlendState anBlendState) override;

	private:
		void SetupRasterizerStates();
		void SetupDepthStencilStates();
		void SetupBlendStates();

		DirectX& myDirectX;

		ID3D11RasterizerState* myRasterizerStates[static_cast<int>(eRasterizer::_RAZTER_COUNT)];
		ID3D11DepthStencilState* myDepthStencilStates[static_cast<int>(eDepthState::_DEPTH_COUNT)];
		ID3D11BlendState* myBlendStates[static_cast<int>(eBlendState::_BLEND_COUNT)];
	};
}