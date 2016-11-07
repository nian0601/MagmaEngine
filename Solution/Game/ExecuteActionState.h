#pragma once

#include "IState.h"

class IGOAPAction;
class ExecuteActionState : public IState
{
public:
	ExecuteActionState(FiniteStateMachine& aStateMachine, Entity& anEntity);
	~ExecuteActionState();

	void Init(IGOAPAction* anAction);
	virtual eStateStatus Update(float aDelta) override;

private:
	void operator=(ExecuteActionState&) = delete;

	IGOAPAction* myAction;
};

