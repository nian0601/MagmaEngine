#pragma once

#include "IState.h"

class Entity;
class MoveToState : public IState
{
public:
	MoveToState(FiniteStateMachine& aStateMachine, Entity& anEntity);
	~MoveToState();

	void Init(Entity* aTargetEntity);
	virtual eStateStatus Update(float aDelta) override;

private:
	Entity* myTargetEntity;
};

