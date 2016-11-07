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
	const CU::GrowingArray<Entity*> GetResources(eResourceType aResourceType) const;

private:
	PollingStation();
	~PollingStation();

	typedef CU::GrowingArray<Entity*> EntityArray;
	CU::StaticArray<EntityArray, eResourceType::_COUNT> myResources;

	static PollingStation* ourInstance;
};

