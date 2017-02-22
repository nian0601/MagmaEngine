#pragma once

#include <IGame.h>
#include <GrowingArray.h>

namespace Magma
{
	class AssetContainer;
	class Camera;
	class RendererProxy;
}

class Entity;
class PollingStation;
class GOAPGameState;

class Game : public Magma::IGame
{
public:
	Game();
	~Game();

	void Init(Magma::Engine& aEngine) override;
	bool Update(float aDelta) override;
	void OnResize(float aWidth, float aHeight) override;

private:
	void CreateWorker();

	void UpdateWorkerStatus();
	void ActivateWorker(Entity* aWorker, const GOAPGameState& aGoalState);

	Magma::Camera* myCamera;
	Magma::RendererProxy* myRendererProxy;
	Magma::AssetContainer* myAssetContainer;

	CU::GrowingArray<Entity*> myEntities;
	CU::GrowingArray<Entity*> myActiveWorkers;
	CU::GrowingArray<Entity*> myIdleWorkers;

	float myAssignWorkTimer;
	int myTargetTreeCount;
	int myTargetWaterCount;
};

