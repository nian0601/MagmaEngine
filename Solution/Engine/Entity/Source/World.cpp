#include "stdafx.h"

#include "../Include/BaseProcessor.h"
#include "../Include/World.h"


namespace Magma
{
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

	void World::SendEvent(const Event& aEvent)
	{
		for each (BaseProcessor* processor in myProcessors)
		{
			processor->OnEvent(aEvent);
		}
	}

	void World::ModifiedEntity(Entity aEntity, int aComponentID, bool aAddedComponent)
	{
		EntityComponentArray components;
		if (!myComponentStorage->GetEntityComponentArray(aEntity, components))
			return;


		for each (BaseProcessor* processor in myProcessors)
		{
			EntityComponentArray modifiedComponents = components;
			const ComponentFilter& filter = processor->GetComponentFilter();

			bool wasRemoved = false;
			bool wasAdded = false;

			if (aAddedComponent)
			{
				bool matchedAfter = filter.Compare(modifiedComponents);
				modifiedComponents[aComponentID] = -1;

				bool matchedBefore = filter.Compare(modifiedComponents);

				if (matchedBefore && !matchedAfter)
					wasRemoved = true;

				if (!matchedBefore && matchedAfter)
					wasAdded = true;
			}
			else
			{
				bool matchedBefore = filter.Compare(modifiedComponents);
				modifiedComponents[aComponentID] = -1;

				bool matchedAfter = filter.Compare(modifiedComponents);

				if (matchedBefore && !matchedAfter)
					wasRemoved = true;

				if (!matchedBefore && matchedAfter)
					wasAdded = true;
			}

			if (wasRemoved)
				processor->EntityRemoved(aEntity);
			

			
		}
	}

}