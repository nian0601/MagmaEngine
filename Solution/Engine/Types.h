#pragma once

namespace Magma
{
	typedef unsigned int EffectID;
	typedef unsigned int EffectVariableID;
	typedef unsigned int ModelID;

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

	enum eBlendState
	{
		NO_BLEND,
		ALPHA_BLEND,
		_BLEND_COUNT
	};
}