#include "stdafx.h"

#include "DirectX.h"
#include "GPUContext.h"
#include "DirectXFactory.h"

namespace Magma
{
	GPUContext::GPUContext(const CU::Vector2<float>& aScreenSize, const HWND& aHwnd)
	{
		myDirectX = new DirectX();
		myDirectX->Init(aHwnd, aScreenSize);

		myGPUFactory = new DirectXFactory(*myDirectX);
	}


	GPUContext::~GPUContext()
	{
		SAFE_DELETE(myGPUFactory);
		SAFE_DELETE(myDirectX);
	}

	void GPUContext::FinishFrame()
	{
		PROFILE_FUNCTION;
		myDirectX->FinishFrame();
	}

	ID3D11Device* GPUContext::GetDevice() const
	{
		return myDirectX->GetDevice();
	}

	ID3D11DeviceContext* GPUContext::GetContext() const
	{
		return myDirectX->GetContext();
	}

	void GPUContext::SetBackbufferAsRenderTarget()
	{
		myDirectX->SetBackbufferAsRenderTarget();
	}

	void GPUContext::GetBackbuffer(Backbuffer& aBackbufferOut)
	{
		myDirectX->GetBackbuffer(aBackbufferOut);
	}

	void GPUContext::SetRasterizerState(eRasterizer anRasterizerState)
	{
		myGPUFactory->SetRasterizerState(anRasterizerState);
	}

	void GPUContext::SetDepthStencilState(eDepthState anDepthStencilState)
	{
		myGPUFactory->SetDepthStencilState(anDepthStencilState);
	}

	void GPUContext::SetBlendState(eBlendState anBlendState)
	{
		myGPUFactory->SetBlendState(anBlendState);
	}
}