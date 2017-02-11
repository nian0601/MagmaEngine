#include "stdafx.h"

#include "Entity.h"
#include "SpriteComponent.h"
#include <AssetContainer.h>
#include <RendererProxy.h>

SpriteComponent::SpriteComponent(Entity& anEntity)
	: IComponent(anEntity)
{
}


SpriteComponent::~SpriteComponent()
{
}

void SpriteComponent::Init(Magma::AssetContainer& anAssetContainer, const CU::String& aFilePath, const CU::Vector2<float>& aSize
	, const CU::Vector2<float>& aScale /*= CU::Vector2<float>(1.f, 1.f)*/, const CU::Vector2<float>& aHotSpot /*= CU::Vector2<float>(0.f, 0.f)*/)
{
	mySizeAndHotSpot.x = aSize.x;
	mySizeAndHotSpot.y = aSize.y;
	mySizeAndHotSpot.z = aHotSpot.x;
	mySizeAndHotSpot.w = aHotSpot.y;

	myPositionAndScale.z = aScale.x;
	myPositionAndScale.w = aScale.y;

	myTexture = anAssetContainer.LoadTexture(aFilePath);
}

void SpriteComponent::Init(Magma::Texture* aTexture, const CU::Vector2<float>& aSize, const CU::Vector2<float>& aScale /*= CU::Vector2<float>(1.f, 1.f)*/, const CU::Vector2<float>& aHotSpot /*= CU::Vector2<float>(0.f, 0.f)*/)
{
	mySizeAndHotSpot.x = aSize.x;
	mySizeAndHotSpot.y = aSize.y;
	mySizeAndHotSpot.z = aHotSpot.x;
	mySizeAndHotSpot.w = aHotSpot.y;

	myPositionAndScale.z = aScale.x;
	myPositionAndScale.w = aScale.y;

	myTexture = aTexture;
}

void SpriteComponent::Update(float)
{
	CU::Vector2<float> entityPosition = myEntity.GetPosition();
	myPositionAndScale.x = entityPosition.x;
	myPositionAndScale.y = entityPosition.y;
}

void SpriteComponent::Render(Magma::RendererProxy& aRendererProxy)
{
	aRendererProxy.RenderSprite(myTexture, myOrientation, mySizeAndHotSpot, myPositionAndScale);
}
