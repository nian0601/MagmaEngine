#pragma once

#include "IState.h"

class MoveToState : public IState
{
public:
	MoveToState(FiniteStateMachine& aStateMachine, Entity& anEntity);
	~MoveToState();

	void Init(const CU::Vector2<float>& aTargetPosition);
	virtual eStateStatus Update(float aDelta) override;

private:
	void operator=(MoveToState&) = delete;

	CU::Vector2<float> myTargetPosition;
};

