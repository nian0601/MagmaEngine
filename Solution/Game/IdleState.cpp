#include "stdafx.h"
#include "IdleState.h"


IdleState::IdleState(FiniteStateMachine& aStateMachine, Entity& anEntity)
	: IState(aStateMachine, anEntity)
{
}


IdleState::~IdleState()
{
}

eStateStatus IdleState::Update(float /*aDelta*/)
{
	return KEEP_STATE;
}
