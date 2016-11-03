#include "stdafx.h"

#include "Entity.h"
#include "MoveToState.h"

MoveToState::MoveToState(FiniteStateMachine& aStateMachine, Entity& anEntity)
	: IState(aStateMachine, anEntity)
	, myTargetEntity(nullptr)
{
}


MoveToState::~MoveToState()
{
}

void MoveToState::Init(Entity* aTargetEntity)
{
	myTargetEntity = aTargetEntity;
}

eStateStatus MoveToState::Update(float aDelta)
{
	DL_ASSERT_EXP(myTargetEntity != nullptr, "MoveToState needs a valid TargetEntity");

	CU::Vector2<float> ownPosition = myEntity.GetPosition();
	CU::Vector2<float> otherPosition = myTargetEntity->GetPosition();
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
