#include "stdafx.h"

#include "Entity.h"
#include "GOAPComponent.h"
#include "PollingStation.h"

#include "FiniteStateMachine.h"
#include "IdleState.h"
#include "MoveToState.h"
#include "ExecuteActionState.h"

#include "GatherWaterAction.h"
#include "GatherWoodAction.h"
#include "CreateDrinkAction.h"
#include "FindGlassAction.h"
#include "CreateGlassDrinkAction.h"

#include "GOAPPlanner.h"
#include "GOAPPlan.h"

GOAPComponent::GOAPComponent(Entity& aEntity)
	: IComponent(aEntity)
	, myStateMachine(nullptr)
	, myActions(8)
	, myPlanner(nullptr)
	, myPlan(nullptr)
{
}


GOAPComponent::~GOAPComponent()
{
	delete myStateMachine;
	myStateMachine = nullptr;
	myActions.DeleteAll();
	delete myPlanner;
	myPlanner = nullptr;
}

void GOAPComponent::Init()
{
	myCurrentResourceType = eResourceType::TREE;

	myStateMachine = new FiniteStateMachine(myEntity);

	myActions.Add(new GatherWaterAction(myEntity));
	myActions.Add(new GatherWoodAction(myEntity));
	myActions.Add(new CreateDrinkAction(myEntity));
	myActions.Add(new FindGlassAction(myEntity));
	myActions.Add(new CreateGlassDrinkAction(myEntity));


	myPlanner = new GOAPPlanner();
	GOAPGameState worldState;
	worldState.SetState(CAN_GATHER_WATER, true);
	worldState.SetState(CAN_GATHER_WOOD, true);

	GOAPGameState goalState;
	goalState.SetState(HAS_DRINK, true);

	myPlan = myPlanner->CreatePlan(myActions, worldState, goalState);
}

void GOAPComponent::Update(float aDeltaTime)
{
	if (myStateMachine->Update(aDeltaTime))
	{
		if (myPlan && !myPlan->IsFinished())
		{
			ExecuteActionState* actionState = myStateMachine->PushState<ExecuteActionState>();
			actionState->Init(myPlan->GetNextAction());
		}
		else
		{
			//Create new plan
		}
	}
}