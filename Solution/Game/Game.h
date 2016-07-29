#pragma once

#include <IGame.h>
#include <GrowingArray.h>
#include <Entity/Include/World.h>

namespace Magma
{
	class AssetContainer;
	class Camera;
	class RendererProxy;
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
	Magma::Camera* myCamera;
	Magma::RendererProxy* myRendererProxy;
};

