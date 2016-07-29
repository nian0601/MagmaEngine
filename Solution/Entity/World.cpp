#include "stdafx.h"

#include "BaseProcessor.h"
#include "World.h"


World::World()
	: myNextEntity(0)
	, myComponentStorage(new ComponentStorage)
	, myProcessors(16)
{
}


World::~World()
{
	SAFE_DELETE(myComponentStorage);
}

Entity World::CreateEntity()
{
	Entity newEntity = myNextEntity++;

	myComponentStorage->AddEntity();

	return newEntity;
}

void World::Update(float aDelta)
{
	for (BaseProcessor* processor : myProcessors)
	{
		processor->Update(aDelta);
	}
}

const CU::GrowingArray<Entity>& World::GetEntities(const ComponentFilter& aFilter)
{
	return myComponentStorage->GetEntities(aFilter);
}
