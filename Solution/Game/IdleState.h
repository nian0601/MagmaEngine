#pragma once

#include "IState.h"
class IdleState : public IState
{
public:
	IdleState(FiniteStateMachine& aStateMachine, Entity& anEntity);
	~IdleState();

	virtual eStateStatus Update(float aDelta) override;

private:
	void operator=(IdleState&) = delete;
};

