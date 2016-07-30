#pragma once

#include <EngineTypes.h>

namespace Magma
{
	class Renderer;
	class Texture;
	class RendererProxy
	{
	public:
		RendererProxy(Renderer& aRenderer);
		~RendererProxy();

		void RenderModel(ModelID aModelID, EffectID aEffectID
			, const CU::Matrix44<float>& aOrientation, const CU::Vector3<float>& aScale = CU::Vector3<float>());
		void RenderSprite(Texture* aTexture, const CU::Matrix44<float>& aOrientation
			, const CU::Vector4<float>& aSizeAndHotSpot, const CU::Vector4<float>& aPositionAndScale);
	private:
		void operator=(RendererProxy&) = delete;

		Renderer& myRenderer;
	};
}