#include "stdafx.h"
#include "StockpileComponent.h"
#include <RendererProxy.h>
#include <AssetContainer.h>
#include "Entity.h"

#include "PollingStation.h"

StockpileComponent::StockpileComponent(Entity& anEntity)
	: IComponent(anEntity)
{
}


StockpileComponent::~StockpileComponent()
{
	PollingStation::GetInstance()->UnregisterStockpile(&myEntity);
}

void StockpileComponent::Init(Magma::AssetContainer& anAssetContainer)
{
	for (int i = 0; i < myResourceTextures.Count(); ++i)
	{
		myResourceTextures[i] = nullptr;
	}

	myResourceTextures[TREE] = anAssetContainer.LoadTexture("Data/Resource/Texture/T_tree_circle.dds");
	myResourceTextures[WATER] = anAssetContainer.LoadTexture("Data/Resource/Texture/T_water_circle.dds");

	mySlots[TOP_LEFT].myTexture = nullptr;
	mySlots[TOP_LEFT].myPositionOffset = { 0.f, 0.f };

	mySlots[TOP_RIGHT].myTexture = nullptr;
	mySlots[TOP_RIGHT].myPositionOffset = { 16.f, 0.f };

	mySlots[BOTTOM_LEFT].myTexture = nullptr;
	mySlots[BOTTOM_LEFT].myPositionOffset = { 0.f, 16.f };

	mySlots[BOTTOM_RIGHT].myTexture = nullptr;
	mySlots[BOTTOM_RIGHT].myPositionOffset = { 16.f, 16.f };

	PollingStation::GetInstance()->RegisterStockpile(&myEntity);
}

void StockpileComponent::Update(float)
{

}

void StockpileComponent::Render(Magma::RendererProxy& aRendererProxy)
{
	CU::Vector4<float> sizeAndHotspot = { 16.f, 16.f, 0.f, 0.f };
	CU::Vector4<float> posAndScale = { 0.f, 0.f, 1.f, 1.f };

	for (const Slot& slot : mySlots)
	{
		if (!slot.myTexture)
			continue;

		posAndScale.x = myEntity.GetPosition().x;
		posAndScale.y = myEntity.GetPosition().y;
		posAndScale.x += slot.myPositionOffset.x;
		posAndScale.y += slot.myPositionOffset.y;

		aRendererProxy.RenderSprite(slot.myTexture, myRenderOrientation, sizeAndHotspot, posAndScale);
	}
}

bool StockpileComponent::IsFull() const
{
	for (const Slot& slot : mySlots)
	{
		if (!slot.myTexture)
			return false;
	}

	return true;
}

bool StockpileComponent::HasResource(eResourceType aResourceType) const
{
	for (const Slot& slot : mySlots)
	{
		if (slot.myTexture && slot.myType == aResourceType)
			return true;
	}

	return false;
}

void StockpileComponent::PlaceResource(eResourceType aResourceType)
{
	for (Slot& slot : mySlots)
	{
		if (!slot.myTexture)
		{
			slot.myTexture = myResourceTextures[aResourceType];
			slot.myType = aResourceType;
			DL_ASSERT_EXP(slot.myTexture, "Found an uninitialized resourcetexture");
			return;
		}
	}

	DL_ASSERT("Tried to place resource on a full stockpile, should not happen");
}

void StockpileComponent::RemoveResource(eResourceType aResourceType)
{
	for (Slot& slot : mySlots)
	{
		if (slot.myTexture && slot.myType == aResourceType)
		{
			slot.myTexture = nullptr;
			return;
		}
	}

	DL_ASSERT("Tried to remove a resource from a stockpile, but couldnt find the resource, should not happen");
}

int StockpileComponent::GetResourceCount(eResourceType aResourceType) const
{
	int count = 0;
	for (const Slot& slot : mySlots)
	{
		if (slot.myTexture && slot.myType == aResourceType)
			++count;
	}

	return count;
}
