#include "stdafx.h"

#include "Renderer.h"
#include "RendererProxy.h"

namespace Magma
{
	RendererProxy::RendererProxy(Renderer& aRenderer)
		: myRenderer(aRenderer)
	{
	}


	RendererProxy::~RendererProxy()
	{
	}

	void RendererProxy::RenderModel(ModelID aModelID, EffectID aEffectID
		, const CU::Matrix44<float>& aOrientation, const CU::Vector3<float>& aScale)
	{
		myRenderer.AddModelCommand(aModelID, aEffectID, aOrientation, aScale);
	}

	void RendererProxy::RenderSprite(Texture* aTexture, const CU::Matrix44<float>& aOrientation, const CU::Vector4<float>& aSizeAndHotSpot, const CU::Vector4<float>& aPositionAndScale)
	{
		myRenderer.AddSpriteCommand(aTexture, aOrientation, aSizeAndHotSpot, aPositionAndScale);
	}

}