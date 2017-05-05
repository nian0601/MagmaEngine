#pragma once

#include <IGame.h>

#include <Types.h>
namespace Magma
{
	class Camera;
	class Engine;
	class RendererProxy;
}

class Game_RTS : public Magma::IGame
{
public:
	Game_RTS();
	~Game_RTS();

	void Init(Magma::Engine& aEngine) override;
	bool Update(float aDelta) override;
	void OnResize(float aWidth, float aHeight) override;

	Magma::ModelID myModelID;
	Magma::EffectID myEffectID;
	Magma::RendererProxy* myRendererProxy;
	Magma::Camera* myCamera;
};

