#include "stdafx.h"

#include "PollingStation.h"
#include "ResourceComponent.h"

ResourceComponent::ResourceComponent(Entity& anEntity)
	: IComponent(anEntity)
	, myResourceType(INVALID)
{
}


ResourceComponent::~ResourceComponent()
{
	switch (myResourceType)
	{
	case TREE:
		myPollingStation->UnregisterResource(&myEntity);
		break;
	default:
		DL_ASSERT("Invalid ResourceType");
		break;
	}
}

void ResourceComponent::Init(eResourceType aResourceType, PollingStation& aPollingStation)
{
	myResourceType = aResourceType;
	myPollingStation = &aPollingStation;

	switch (myResourceType)
	{
	case INVALID:
	case _COUNT:
		DL_ASSERT("Invalid ResourceType");
		break;
	default:
		myPollingStation->RegisterResource(&myEntity);
		break;
	}
}

void ResourceComponent::Update(float)
{
}
