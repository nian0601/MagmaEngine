#pragma once

#include "IComponent.h"
#include "EntityDefines.h"

class FiniteStateMachine;
class IGOAPAction;
class GOAPPlanner;
class GOAPPlan;

class GOAPComponent : public IComponent
{
public:
	GOAPComponent(Entity& aEntity);
	~GOAPComponent();

	void Init();

	virtual void Update(float) override;

private:
	eResourceType myCurrentResourceType;

	FiniteStateMachine* myStateMachine;
	GOAPPlanner* myPlanner;
	GOAPPlan* myPlan;

	CU::GrowingArray<IGOAPAction*> myActions;
};

