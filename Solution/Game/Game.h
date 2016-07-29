#pragma once

#include <IGame.h>
#include <GrowingArray.h>
#include <World.h>

namespace Easy3D
{
	class AssetContainer;
	class Camera;
}

namespace CU
{
	class TimerManager;
}

class Game : public Easy3D::IGame
{
public:
	Game();
	~Game();

	void Init(Easy3D::Engine& aEngine) override;
	bool Update(float aDelta) override;
	void OnResize(float aWidth, float aHeight) override;

private:
	void UpdateCamera(float aDelta);
	void LoadLevel(Easy3D::AssetContainer& aAssetContainer);

	Easy3D::Camera* myCamera;

	World myWorld;
};

