#include "stdafx.h"
#include "PollingStation.h"
#include "Entity.h"
#include "ResourceComponent.h"
#include "StockpileComponent.h"

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
	for (int i = 0; i < eResourceType::_RESOURCE_COUNT; ++i)
		myResources[i].Init(16);

	myStockpiles.Init(16);
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

void PollingStation::RegisterStockpile(Entity* anEntity)
{
	myStockpiles.AddUnique(anEntity);
}

void PollingStation::UnregisterStockpile(Entity* anEntity)
{
	myStockpiles.RemoveCyclic(anEntity);
}

const CU::GrowingArray<Entity*> PollingStation::GetResources(eResourceType aResourceType) const
{
	DL_ASSERT_EXP(aResourceType > INVALID && aResourceType < _RESOURCE_COUNT, "Invalid resource type");

	return myResources[aResourceType];
}

Entity* PollingStation::FindFreeStockpile() const
{
	for (int i = 0; i < myStockpiles.Size(); ++i)
	{
		StockpileComponent* pileComponent = myStockpiles[i]->GetComponent<StockpileComponent>();
		if (pileComponent && !pileComponent->IsFull())
			return myStockpiles[i];
	}

	return nullptr;
}

int PollingStation::GetResourceCount(eResourceType aResourceType) const
{
	DL_ASSERT_EXP(aResourceType > INVALID && aResourceType < _RESOURCE_COUNT, "Invalid resource type");

	int count = 0;
	for (int i = 0; i < myStockpiles.Size(); ++i)
	{
		StockpileComponent* pileComponent = myStockpiles[i]->GetComponent<StockpileComponent>();
		if (pileComponent)
			count += pileComponent->GetResourceCount(aResourceType);
	}

	return count;
}
