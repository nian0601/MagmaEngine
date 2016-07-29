#include "stdafx.h"

#include "Instance.h"
#include "Scene.h"

namespace Easy3D
{
	Scene::Scene()
		: myCamera(nullptr)
		, myInstances(16)
		, myPointLights(16)
	{
	}


	Scene::~Scene()
	{
	}

	void Scene::Render(Renderer* aRenderer)
	{
		DL_ASSERT_EXP(myCamera != nullptr, "Cant render without a Camera");

		//aRenderer->BeginModelBatch();

		for (Instance* instance : myInstances)
		{
			instance->Render(aRenderer, *myCamera);
		}

		//aRenderer->EndModelBatch();
	}

	void Scene::Render()
	{
		for (Instance* instance : myInstances)
		{
			instance->Render();
		}
	}

	void Scene::SetCamera(Camera& aCamera)
	{
		myCamera = &aCamera;
	}

	void Scene::AddInstance(Instance* aInstance)
	{
		myInstances.Add(aInstance);
	}

	void Scene::RemoveInstance(Instance* aInstance)
	{
		DL_ASSERT_EXP(myInstances.Find(aInstance) != myInstances.FoundNone, "Cant remove Instance thats not in the scene");
		myInstances.RemoveCyclic(aInstance);
	}

	void Scene::AddLight(PointLight* aLight)
	{
		myPointLights.Add(aLight);
	}

}