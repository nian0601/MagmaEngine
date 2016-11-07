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
		PollingStation::GetInstance()->UnregisterResource(&myEntity);
		break;
	default:
		DL_ASSERT("Invalid ResourceType");
		break;
	}
}

void ResourceComponent::Init(eResourceType aResourceType)
{
	myResourceType = aResourceType;

	switch (myResourceType)
	{
	case INVALID:
	case _COUNT:
		DL_ASSERT("Invalid ResourceType");
		break;
	default:
		PollingStation::GetInstance()->RegisterResource(&myEntity);
		break;
	}
}

void ResourceComponent::Update(float)
{
}
