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
#include "DeliverWaterAction.h"
#include "DeliverWoodAction.h"

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
	myStateMachine = new FiniteStateMachine(myEntity);

	myActions.Add(new GatherWaterAction(myEntity));
	myActions.Add(new GatherWoodAction(myEntity));
	myActions.Add(new CreateDrinkAction(myEntity));
	myActions.Add(new FindGlassAction(myEntity));
	myActions.Add(new CreateGlassDrinkAction(myEntity));
	myActions.Add(new DeliverWaterAction(myEntity));
	myActions.Add(new DeliverWoodAction(myEntity));

	myPlanner = new GOAPPlanner();
}

void GOAPComponent::Update(float aDeltaTime)
{
	if (myStateMachine->Update(aDeltaTime) && myPlan)
	{
		if (myPlan->IsFinished())
		{
			myStateMachine->PopAll();
			SAFE_DELETE(myPlan);
		}
		else
		{
			ExecuteActionState* actionState = myStateMachine->PushState<ExecuteActionState>();
			actionState->Init(myPlan->GetNextAction());
		}
	}
}

void GOAPComponent::StartPlan(GOAPGameState aGoalState)
{
	if (myPlan)
	{
		myStateMachine->PopAll();
		SAFE_DELETE(myPlan);
	}

	myStartState.SetEntityState(myEntity.GetGOAPState());
	myPlan = myPlanner->CreatePlan(myActions, myStartState, aGoalState);
}
