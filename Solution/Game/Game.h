#pragma once

#include <IGame.h>
#include <GrowingArray.h>
#include <World.h>

namespace Magma
{
	class AssetContainer;
	class Camera;
}

namespace CU
{
	class TimerManager;
}

class Game : public Magma::IGame
{
public:
	Game();
	~Game();

	void Init(Magma::Engine& aEngine) override;
	bool Update(float aDelta) override;
	void OnResize(float aWidth, float aHeight) override;

private:
	void UpdateCamera(float aDelta);
	void LoadLevel(Magma::AssetContainer& aAssetContainer);

	Magma::Camera* myCamera;

	World myWorld;
};

