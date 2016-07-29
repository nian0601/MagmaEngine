#pragma once
#include "FullscreenQuad.h"

namespace Easy3D
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
		DeferredRenderer(AssetContainer& aAssetContainer, GPUContext& aGPUContext, const CU::Vector2<float>& aWindowSize);
		~DeferredRenderer();

		void Render(Scene* aScene);

		void Resize(float aWidth, float aHeight);

	private:
		void RenderToGBuffer(Scene* aScene);
		void RenderAmbientPass(const Camera& aCamera);
		void RenderPointLights(Scene* aScene);

		EffectID myFullscreenEffect;
		EffectID myPointLightEffect;
		GBuffer* myGBuffer;
		Texture* myCubemap;

		Renderer* myRenderer;
		Instance* myPointLightInstance;
	};
}