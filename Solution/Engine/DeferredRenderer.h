#pragma once
#include "FullscreenQuad.h"

namespace Magma
{
	class AssetContainer;
	class Camera;
	class Effect;
	class GBuffer;
	class GPUContext;
	class Instance;
	class Scene;
	class Texture;
	class Renderer;

	class DeferredRenderer
	{
	public:
		DeferredRenderer(AssetContainer& aAssetContainer, GPUContext& aGPUContext,
			Renderer& aRenderer, const CU::Vector2<float>& aWindowSize);
		~DeferredRenderer();

		void Render(Scene* aScene);

		void Resize(float aWidth, float aHeight);

	private:
		void operator=(DeferredRenderer&) = delete;

		void RenderToGBuffer(Scene* aScene);
		void RenderAmbientPass(const Camera& aCamera);
		void RenderPointLights(Scene* aScene);

		EffectID myFullscreenEffect;
		EffectID myPointLightEffect;
		GBuffer* myGBuffer;
		Texture* myCubemap;

		Renderer& myRenderer;
		Instance* myPointLightInstance;
	};
}