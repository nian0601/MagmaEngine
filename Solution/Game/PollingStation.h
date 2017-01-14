#pragma once

#include <GrowingArray.h>
#include <StaticArray.h>

#include "EntityDefines.h"

class Entity;
class PollingStation
{
public:
	static PollingStation* GetInstance();
	static void Destroy();

	void RegisterResource(Entity* anEntity);
	void UnregisterResource(Entity* anEntity);

	void RegisterStockpile(Entity* anEntity);
	void UnregisterStockpile(Entity* anEntity);

	const CU::GrowingArray<Entity*> GetResources(eResourceType aResourceType) const;
	Entity* FindFreeStockpile() const;

private:
	PollingStation();
	~PollingStation();

	typedef CU::GrowingArray<Entity*> EntityArray;
	CU::StaticArray<EntityArray, eResourceType::_RESOURCE_COUNT> myResources;
	
	EntityArray myStockpiles;

	static PollingStation* ourInstance;
};

