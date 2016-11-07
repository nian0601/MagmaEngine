#include "stdafx.h"

#include "Entity.h"
#include "MoveToState.h"

MoveToState::MoveToState(FiniteStateMachine& aStateMachine, Entity& anEntity)
	: IState(aStateMachine, anEntity)
{
}


MoveToState::~MoveToState()
{
}

void MoveToState::Init(const CU::Vector2<float>& aTargetPosition)
{
	myTargetPosition = aTargetPosition;
}

eStateStatus MoveToState::Update(float aDelta)
{
	CU::Vector2<float> ownPosition = myEntity.GetPosition();
	CU::Vector2<float> otherPosition = myTargetPosition;
	CU::Vector2<float> direction = otherPosition - ownPosition;
	float distance = CU::Length(direction);
	CU::Normalize(direction);

	ownPosition += direction * 100.f * aDelta;

	myEntity.SetPosition(ownPosition);

	if (distance < 10.f)
	{
		return POP_STATE;
	}
	return KEEP_STATE;
}
