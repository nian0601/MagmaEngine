#include "stdafx.h"

#include "ExecuteActionState.h"
#include "FiniteStateMachine.h"
#include "IGOAPAction.h"
#include "MoveToState.h"

ExecuteActionState::ExecuteActionState(FiniteStateMachine& aStateMachine, Entity& anEntity)
	: IState(aStateMachine, anEntity)
	, myAction(nullptr)
{
}


ExecuteActionState::~ExecuteActionState()
{
}

void ExecuteActionState::Init(IGOAPAction* anAction)
{
	myAction = anAction;
	myAction->Init();
	if (!myAction->IsInRange())
	{
		MoveToState* moveToState = myStateMachine.PushState<MoveToState>();
		moveToState->Init(myAction->GetTargetPosition());
	}
}

eStateStatus ExecuteActionState::Update(float aDelta)
{
	DL_ASSERT_EXP(myAction != nullptr, "Invalid Action in ExecuteActionState");

	if (myAction->Update(aDelta))
		return POP_STATE;

	return KEEP_STATE;
}
