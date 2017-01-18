#pragma once

#include "IState.h"

class GOAPAction;
class ExecuteActionState : public IState
{
public:
	ExecuteActionState(FiniteStateMachine& aStateMachine, Entity& anEntity);
	~ExecuteActionState();

	void Init(GOAPAction* anAction);
	virtual eStateStatus Update(float aDelta) override;

private:
	void operator=(ExecuteActionState&) = delete;

	GOAPAction* myAction;
};

