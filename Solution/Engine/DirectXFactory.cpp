#include "stdafx.h"
#include "DirectXFactory.h"
#include "DirectX.h"

#include <d3d11.h>

namespace Magma
{
	DirectXFactory::DirectXFactory(DirectX& anDirectX)
		: myDirectX(anDirectX)
	{
		SetupRasterizerStates();
		SetupDepthStencilStates();
		SetupBlendStates();
	}


	DirectXFactory::~DirectXFactory()
	{
	}

	void DirectXFactory::SetRasterizerState(eRasterizer anRasterizerState)
	{
		myDirectX.GetContext()->RSSetState(myRasterizerStates[anRasterizerState]);
	}

	void DirectXFactory::SetDepthStencilState(eDepthState anDepthStencilState)
	{
		myDirectX.GetContext()->OMSetDepthStencilState(myDepthStencilStates[anDepthStencilState], 1);
	}

	void DirectXFactory::SetBlendState(eBlendState anBlendState)
	{
		float blendFactor[4];
		blendFactor[0] = 0.f;
		blendFactor[1] = 0.f;
		blendFactor[2] = 0.f;
		blendFactor[3] = 0.f;

		myDirectX.GetContext()->OMSetBlendState(myBlendStates[anBlendState], blendFactor, 0xFFFFFFFF);
	}

	void DirectXFactory::SetupRasterizerStates()
	{
		D3D11_RASTERIZER_DESC desc;
		ZeroMemory(&desc, sizeof(D3D11_RASTERIZER_DESC));
		desc.FrontCounterClockwise = false;
		desc.DepthBias = false;
		desc.DepthBiasClamp = 0;
		desc.SlopeScaledDepthBias = 0;
		desc.DepthClipEnable = false;
		desc.ScissorEnable = false;
		desc.MultisampleEnable = false;
		desc.AntialiasedLineEnable = false;


		desc.FillMode = D3D11_FILL_WIREFRAME;
		desc.CullMode = D3D11_CULL_BACK;
		myDirectX.GetDevice()->CreateRasterizerState(&desc, &myRasterizerStates[static_cast<int>(eRasterizer::WIRE_FRAME)]);


		desc.FillMode = D3D11_FILL_SOLID;
		desc.CullMode = D3D11_CULL_BACK;
		myDirectX.GetDevice()->CreateRasterizerState(&desc, &myRasterizerStates[static_cast<int>(eRasterizer::CULL_BACK)]);

		desc.FillMode = D3D11_FILL_SOLID;
		desc.CullMode = D3D11_CULL_NONE;
		myDirectX.GetDevice()->CreateRasterizerState(&desc, &myRasterizerStates[static_cast<int>(eRasterizer::NO_CULLING)]);
	}

	void DirectXFactory::SetupDepthStencilStates()
	{
		D3D11_DEPTH_STENCIL_DESC  stencilDesc;
		stencilDesc.DepthFunc = D3D11_COMPARISON_LESS;
		stencilDesc.StencilEnable = true;
		stencilDesc.StencilReadMask = 0xFF;
		stencilDesc.StencilWriteMask = 0xFF;
		stencilDesc.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
		stencilDesc.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_INCR;
		stencilDesc.FrontFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
		stencilDesc.FrontFace.StencilFunc = D3D11_COMPARISON_ALWAYS;
		stencilDesc.BackFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
		stencilDesc.BackFace.StencilDepthFailOp = D3D11_STENCIL_OP_DECR;
		stencilDesc.BackFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
		stencilDesc.BackFace.StencilFunc = D3D11_COMPARISON_ALWAYS;


		stencilDesc.DepthEnable = true;
		stencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
		HRESULT hr = myDirectX.GetDevice()->CreateDepthStencilState(&stencilDesc, &myDepthStencilStates[static_cast<int>(eDepthState::ENABLED)]);
		DL_ASSERT_EXP(FAILED(hr) == false, "Failed to create ENABLED depthstate");

		stencilDesc.DepthEnable = false;
		stencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
		hr = myDirectX.GetDevice()->CreateDepthStencilState(&stencilDesc, &myDepthStencilStates[static_cast<int>(eDepthState::DISABLED)]);
		DL_ASSERT_EXP(FAILED(hr) == false, "Failed to create DISABLED depthstate");

		stencilDesc.DepthEnable = false;
		stencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ZERO;
		stencilDesc.StencilEnable = false;
		stencilDesc.StencilReadMask = UINT8(0xFF);
		stencilDesc.StencilWriteMask = 0x0;
		hr = myDirectX.GetDevice()->CreateDepthStencilState(&stencilDesc, &myDepthStencilStates[static_cast<int>(eDepthState::NO_READ_NO_WRITE)]);
		DL_ASSERT_EXP(FAILED(hr) == false, "Failed to create NO_READ_NO_WRITE depthstate");

		stencilDesc.DepthEnable = true;
		stencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ZERO;
		stencilDesc.DepthFunc = D3D11_COMPARISON_GREATER_EQUAL;
		stencilDesc.StencilEnable = false;
		stencilDesc.StencilReadMask = UINT8(0xFF);
		stencilDesc.StencilWriteMask = 0x0;

		stencilDesc.FrontFace.StencilFailOp = D3D11_STENCIL_OP_ZERO;
		stencilDesc.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_ZERO;
		stencilDesc.FrontFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
		stencilDesc.FrontFace.StencilFunc = D3D11_COMPARISON_EQUAL;

		stencilDesc.BackFace.StencilFailOp = D3D11_STENCIL_OP_ZERO;
		stencilDesc.BackFace.StencilDepthFailOp = D3D11_STENCIL_OP_ZERO;
		stencilDesc.BackFace.StencilPassOp = D3D11_STENCIL_OP_ZERO;
		stencilDesc.BackFace.StencilFunc = D3D11_COMPARISON_NEVER;

		hr = myDirectX.GetDevice()->CreateDepthStencilState(&stencilDesc, &myDepthStencilStates[static_cast<int>(eDepthState::READ_NO_WRITE)]);
		DL_ASSERT_EXP(FAILED(hr) == false, "Failed to create READ_NO_WRITE depthstate");
	}

	void DirectXFactory::SetupBlendStates()
	{
		D3D11_BLEND_DESC blendDesc;
		ZeroMemory(&blendDesc, sizeof(blendDesc));
		blendDesc.AlphaToCoverageEnable = true;
		blendDesc.IndependentBlendEnable = false;
		blendDesc.RenderTarget[0].BlendEnable = TRUE;
		blendDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_ONE;
		blendDesc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
		blendDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
		blendDesc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_SRC_ALPHA;
		blendDesc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_DEST_ALPHA;
		blendDesc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
		blendDesc.RenderTarget[0].RenderTargetWriteMask = 0x0f;


		HRESULT hr = myDirectX.GetDevice()->CreateBlendState(&blendDesc, &myBlendStates[static_cast<int>(eBlendState::ALPHA_BLEND)]);
		if (FAILED(hr) != S_OK)
		{
			DL_ASSERT("Failed to CreateAlphaBlendState");
		}

		blendDesc.AlphaToCoverageEnable = false;
		blendDesc.IndependentBlendEnable = false;
		blendDesc.RenderTarget[0].BlendEnable = FALSE;
		blendDesc.RenderTarget[0].RenderTargetWriteMask = 0x0f;

		hr = myDirectX.GetDevice()->CreateBlendState(&blendDesc, &myBlendStates[static_cast<int>(eBlendState::NO_BLEND)]);
		if (FAILED(hr) != S_OK)
		{
			DL_ASSERT("Failed to CreateNoAlphaBlendState");
		}
	}

}