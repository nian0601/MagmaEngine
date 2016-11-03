#pragma once

#include <GrowingArray.h>
#include <StaticArray.h>

#include "EntityDefines.h"

class Entity;
class PollingStation
{
public:
	PollingStation();
	~PollingStation();

	void RegisterResource(Entity* anEntity);
	void UnregisterResource(Entity* anEntity);
	const CU::GrowingArray<Entity*> GetResources(eResourceType aResourceType) const;

private:
	typedef CU::GrowingArray<Entity*> EntityArray;
	CU::StaticArray<EntityArray, eResourceType::_COUNT> myResources;
};

