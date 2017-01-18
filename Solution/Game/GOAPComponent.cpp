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
	myCurrentResourceType = eResourceType::TREE;

	myStateMachine = new FiniteStateMachine(myEntity);

	myActions.Add(new GatherWaterAction(myEntity));
	myActions.Add(new GatherWoodAction(myEntity));
	myActions.Add(new CreateDrinkAction(myEntity));
	myActions.Add(new FindGlassAction(myEntity));
	myActions.Add(new CreateGlassDrinkAction(myEntity));
	myActions.Add(new DeliverWaterAction(myEntity));
	myActions.Add(new DeliverWoodAction(myEntity));

	myPlanner = new GOAPPlanner();

	myGoalState.SetWorldState(eWorldState::HAS_WATER_ON_STOCKPILE, true);
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
			if (myGoalState.IsWorldStateSet(eWorldState::HAS_WOOD_ON_STOCKPILE))
			{
				myGoalState.ResetWorldState(eWorldState::HAS_WOOD_ON_STOCKPILE);
				myGoalState.SetWorldState(eWorldState::HAS_WATER_ON_STOCKPILE, true);
			}
			else
			{
				myGoalState.SetWorldState(eWorldState::HAS_WOOD_ON_STOCKPILE, true);
				myGoalState.ResetWorldState(eWorldState::HAS_WATER_ON_STOCKPILE);
			}

			myStartState.SetEntityState(myEntity.GetGOAPState());

			delete myPlan;
			myPlan = myPlanner->CreatePlan(myActions, myStartState, myGoalState);
		}
	}

	if (myPlan && !myPlan->CheckDynamicCondition())
	{
		myStateMachine->PopAll();
		delete myPlan;
		myPlan = myPlanner->CreatePlan(myActions, myStartState, myGoalState);
	}
}