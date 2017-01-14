#pragma once

#include <CUString.h>
#include "IComponent.h"
#include <Vector.h>


namespace Magma
{
	class AssetContainer;
	class Texture;
}

class SpriteComponent : public IComponent
{
public:
	SpriteComponent(Entity& anEntity);
	~SpriteComponent();

	virtual void Init(Magma::AssetContainer& anAssetContainer, const CU::String& aFilePath, const CU::Vector2<float>& aSize
		, const CU::Vector2<float>& aScale = CU::Vector2<float>(1.f, 1.f), const CU::Vector2<float>& aHotSpot = CU::Vector2<float>(0.f, 0.f));
	virtual void Init(Magma::Texture* aTexture, const CU::Vector2<float>& aSize
		, const CU::Vector2<float>& aScale = CU::Vector2<float>(1.f, 1.f), const CU::Vector2<float>& aHotSpot = CU::Vector2<float>(0.f, 0.f));
	virtual void Update(float) override;
	virtual void Render(Magma::RendererProxy& aRendererProxy) override;

private:
	CU::Vector4<float> mySizeAndHotSpot;
	CU::Vector4<float> myPositionAndScale;
	CU::Matrix44<float> myOrientation;
	Magma::Texture* myTexture;
};

