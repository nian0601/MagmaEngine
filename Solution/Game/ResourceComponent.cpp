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
	PollingStation::GetInstance()->RegisterResource(&myEntity);
}
