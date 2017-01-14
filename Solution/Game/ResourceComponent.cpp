#include "stdafx.h"

#include "PollingStation.h"
#include "ResourceComponent.h"
#include <Rendering\AssetContainer.h>

ResourceComponent::ResourceComponent(Entity& anEntity)
	: IComponent(anEntity)
	, myResourceType(INVALID)
	, myStockpileTexture(nullptr)
{
}


ResourceComponent::~ResourceComponent()
{
	switch (myResourceType)
	{
	case TREE:
		PollingStation::GetInstance()->UnregisterResource(&myEntity);
		break;
	default:
		DL_ASSERT("Invalid ResourceType");
		break;
	}
}

void ResourceComponent::Init(eResourceType aResourceType, Magma::AssetContainer& anAssetContainer)
{
	myResourceType = aResourceType;

	switch (myResourceType)
	{
	case INVALID:
	case _RESOURCE_COUNT:
		DL_ASSERT("Invalid ResourceType");
		break;
	case TREE:
		anAssetContainer.LoadTexture("Data/Resource/Texture/T_tree_circle.dds");
		break;
	case WATER:
		anAssetContainer.LoadTexture("Data/Resource/Texture/T_water_circle.dds");
		break;
	}

	PollingStation::GetInstance()->RegisterResource(&myEntity);
}
