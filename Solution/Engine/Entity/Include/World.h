#pragma once

#include "ComponentStorage.h"
#include "CustomEntityTypes.h"
#include "TypeID.h"
#include <GrowingArray.h>


namespace Magma
{
	struct ComponentFilter;
	struct Event;

	class BaseProcessor;
	class World
	{
	public:
		World();
		~World();

		Entity CreateEntity();
		void Update(float aDelta);
		const CU::GrowingArray<Entity>& GetEntities(const ComponentFilter& aFilter);

		template<typename T>
		void AddComponent(Entity aEntity);

		template<typename T>
		void RemoveComponent(Entity aEntity);

		template<typename T>
		T& GetComponent(Entity aEntity);

		template<typename T>
		bool HasComponent(Entity aEntity);

		template<typename T>
		void AddProcessor();

		template<typename T>
		void AddProcessor(T* aProcessor);

		void SendEvent(const Event& aEvent);



		void ModifiedEntity(Entity aEntity, int aComponentID, bool aAddedComponent);

	private:
		Entity myNextEntity;

		ComponentStorage* myComponentStorage;
		CU::GrowingArray<BaseProcessor*> myProcessors;
	};


	template<typename T>
	void World::AddComponent(Entity aEntity)
	{
		T* component = new T();
		unsigned int componentID = TypeID<BaseComponent>::GetID<T>();
		myComponentStorage->AddComponent(aEntity, component, componentID);
		ModifiedEntity(aEntity, componentID, true);
	}

	template<typename T>
	void World::RemoveComponent(Entity aEntity)
	{
		unsigned int componentID = TypeID<BaseComponent>::GetID<T>();
		ModifiedEntity(aEntity, componentID, false);
		myComponentStorage->RemoveComponent(aEntity, componentID);
	}

	template<typename T>
	T& World::GetComponent(Entity aEntity)
	{
		return static_cast<T&>(myComponentStorage->GetComponent(aEntity, TypeID<BaseComponent>::GetID<T>()));
	}

	template<typename T>
	bool World::HasComponent(Entity aEntity)
	{
		return myComponentStorage->HasComponent(aEntity, TypeID<BaseComponent>::GetID<T>());
	}

	template<typename T>
	void World::AddProcessor()
	{
		myProcessors.Add(new T(*this));
	}

	template<typename T>
	void World::AddProcessor(T* aProcessor)
	{
		myProcessors.Add(aProcessor);
	}
}