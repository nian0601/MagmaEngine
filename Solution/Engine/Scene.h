#pragma once
#include <GrowingArray.h>

namespace Easy3D
{
	class Camera;
	class Instance;
	class Renderer;
	class PointLight;
	
	class Scene
	{
	public:
		Scene();
		~Scene();

		void Render();
		void Render(Renderer* aRenderer);

		void SetCamera(Camera& aCamera);

		void AddInstance(Instance* aInstance);
		void RemoveInstance(Instance* aInstance);

		void AddLight(PointLight* aLight);

		const CU::GrowingArray<PointLight*>& GetPointLights() const;
		const Camera& GetCamera() const;

	private:
		CU::GrowingArray<Instance*> myInstances;
		CU::GrowingArray<PointLight*> myPointLights;
		Camera* myCamera;
	};

	inline const CU::GrowingArray<PointLight*>& Scene::GetPointLights() const
	{
		return myPointLights;
	}

	inline const Camera& Scene::GetCamera() const
	{
		return *myCamera;
	}
}