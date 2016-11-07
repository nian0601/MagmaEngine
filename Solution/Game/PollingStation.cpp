#include "stdafx.h"
#include "PollingStation.h"
#include "Entity.h"
#include "ResourceComponent.h"

PollingStation* PollingStation::ourInstance = nullptr;
PollingStation* PollingStation::GetInstance()
{
	if (!ourInstance)
		ourInstance = new PollingStation();

	return ourInstance;
}

void PollingStation::Destroy()
{
	delete ourInstance;
	ourInstance = nullptr;
}

PollingStation::PollingStation()
{
	for (int i = 0; i < eResourceType::_COUNT; ++i)
		myResources[i].Init(16);
}


PollingStation::~PollingStation()
{
}


void PollingStation::RegisterResource(Entity* anEntity)
{
	ResourceComponent* resource = anEntity->GetComponent<ResourceComponent>();
	if (resource)
	{
		eResourceType type = resource->GetResourceType();
		myResources[type].Add(anEntity);
	}
}

void PollingStation::UnregisterResource(Entity* anEntity)
{
	ResourceComponent* resource = anEntity->GetComponent<ResourceComponent>();
	if (resource)
	{
		eResourceType type = resource->GetResourceType();
		EntityArray& resourceArray = myResources[type];

		int index = resourceArray.Find(anEntity);
		DL_ASSERT_EXP(index != -1, "Couldnt find entity to unregister");

		resourceArray.RemoveCyclicAtIndex(index);
	}
}

const CU::GrowingArray<Entity*> PollingStation::GetResources(eResourceType aResourceType) const
{
	DL_ASSERT_EXP(aResourceType > INVALID && aResourceType < _COUNT, "Invalid resource type");

	return myResources[aResourceType];
}
