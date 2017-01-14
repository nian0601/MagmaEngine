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

	myWorldState.SetState(CAN_GATHER_WATER, true);
	myWorldState.SetState(CAN_GATHER_WOOD, true);

	myGoalState.SetState(HAS_WATER_ON_STOCKPILE, true);

	myPlan = myPlanner->CreatePlan(myActions, myWorldState, myGoalState);
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
			if (myGoalState.IsSet(HAS_WOOD_ON_STOCKPILE))
			{
				myGoalState.ResetState(HAS_WOOD_ON_STOCKPILE);
				myGoalState.SetState(HAS_WATER_ON_STOCKPILE, true);
			}
			else
			{
				myGoalState.SetState(HAS_WOOD_ON_STOCKPILE, true);
				myGoalState.ResetState(HAS_WATER_ON_STOCKPILE);
			}

			myPlan = myPlanner->CreatePlan(myActions, myWorldState, myGoalState);
		}
	}
}