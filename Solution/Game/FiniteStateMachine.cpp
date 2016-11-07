#include "stdafx.h"

#include "FiniteStateMachine.h"
#include "IState.h"

FiniteStateMachine::FiniteStateMachine(Entity& anEntity)
	: myEntity(anEntity)
	, myStates(8)
{
}


FiniteStateMachine::~FiniteStateMachine()
{
	for (int i = myStates.Size() - 1; i >= 0; --i)
		myStates.DeleteCyclicAtIndex(i);
}

bool FiniteStateMachine::Update(float aDelta)
{
	if (myStates.Size() == 0)
		return true;

	eStateStatus currentStatus = myStates.GetLast()->Update(aDelta);

	if (currentStatus == POP_STATE)
		myStates.DeleteCyclicAtIndex(myStates.Size() - 1);

	return false;
}
