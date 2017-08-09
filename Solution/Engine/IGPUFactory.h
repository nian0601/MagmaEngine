#pragma once

namespace Magma
{
	class IGPUFactory
	{
	public:
		virtual ~IGPUFactory() {};

		virtual void SetRasterizerState(eRasterizer anRasterizerState) = 0;
		virtual void SetDepthStencilState(eDepthState anDepthState) = 0;
		virtual void SetBlendState(eBlendState anBlendState) = 0;

	protected:
		IGPUFactory() {};
	};
}

