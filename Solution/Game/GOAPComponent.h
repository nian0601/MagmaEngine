#pragma once

#include "IComponent.h"
#include "EntityDefines.h"

class PollingStation;
class FiniteStateMachine;

class GOAPComponent : public IComponent
{
public:
	GOAPComponent(Entity& aEntity);
	~GOAPComponent();

	void Init(PollingStation* aPollingStation);

	virtual void Update(float) override;

private:
	Entity* GetClosestEntity(const CU::GrowingArray<Entity*>& someEntities) const;

	PollingStation* myPollingStation;
	eResourceType myCurrentResourceType;
	Entity* myTargetEntity;

	FiniteStateMachine* myStateMachine;
};

