#pragma once

#include "IComponent.h"
#include "EntityDefines.h"
#include "GOAPGameState.h"
class FiniteStateMachine;
class GOAPAction;
class GOAPPlanner;
class GOAPPlan;

class GOAPComponent : public IComponent
{
public:
	GOAPComponent(Entity& aEntity);
	~GOAPComponent();

	void Init();

	virtual void Update(float) override;

	void StartPlan(GOAPGameState aGoalState);
	bool HasActivePlan() const { return myPlan != nullptr; }

private:
	FiniteStateMachine* myStateMachine;
	GOAPPlanner* myPlanner;
	GOAPPlan* myPlan;

	CU::GrowingArray<GOAPAction*> myActions;

	GOAPGameState myStartState;
};

