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

GOAPComponent::GOAPComponent(Entity& aEntity)
	: IComponent(aEntity)
	, myStateMachine(nullptr)
	, myActions(8)
{
}


GOAPComponent::~GOAPComponent()
{
	delete myStateMachine;
	myStateMachine = nullptr;
	myActions.DeleteAll();
}

void GOAPComponent::Init()
{
	myCurrentResourceType = eResourceType::TREE;

	myStateMachine = new FiniteStateMachine(myEntity);

	myActions.Add(new GatherWaterAction(myEntity));
	myActions.Add(new GatherWoodAction(myEntity));
	myActions.Add(new GatherWaterAction(myEntity));
	myActions.Add(new GatherWoodAction(myEntity));

	ExecuteActionState* actionState = myStateMachine->PushState<ExecuteActionState>();
	actionState->Init(myActions.GetLast());
}

void GOAPComponent::Update(float aDeltaTime)
{
	if (myStateMachine->Update(aDeltaTime))
	{
		if (myActions.Size() > 1)
		{
			myActions.DeleteCyclicAtIndex(myActions.Size()-1);
			ExecuteActionState* actionState = myStateMachine->PushState<ExecuteActionState>();
			actionState->Init(myActions.GetLast());
		}
	}
}