#pragma once
#include <Vector.h>

struct ID3D11Device;
struct ID3D11DeviceContext;

namespace Magma
{
	struct Backbuffer;

	class DirectX;
	class IGPUFactory;

	class GPUContext
	{
	public:
		GPUContext(const CU::Vector2<float>& aScreenSize, const HWND& aHwnd);
		~GPUContext();

		void FinishFrame();

		ID3D11Device* GetDevice() const;
		ID3D11DeviceContext* GetContext() const;

		void SetBackbufferAsRenderTarget();
		void GetBackbuffer(Backbuffer& aBackbufferOut);

		void SetRasterizerState(eRasterizer anRasterizerState);
		void SetDepthStencilState(eDepthState anDepthStencilState);
		void SetBlendState(eBlendState anBlendState);

	private:
		DirectX* myDirectX;
		IGPUFactory* myGPUFactory;
	};
}