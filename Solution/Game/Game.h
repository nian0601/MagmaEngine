#pragma once

#include <IGame.h>
#include <GrowingArray.h>
#include <Entity/Include/World.h>

#include <Matrix.h>
#include <Vector.h>

namespace Magma
{
	class AssetContainer;
	class Camera;
	class RendererProxy;

	class Texture;
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

	Magma::Texture* mySpriteTexture;
	CU::Matrix44<float> mySpriteOrientation;
	CU::Vector4<float> mySizeAndHotspot;
	CU::Vector4<float> myPositionAndScale;
};

