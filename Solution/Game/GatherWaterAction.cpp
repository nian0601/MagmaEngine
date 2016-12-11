#include "stdafx.h"
#include "GatherWaterAction.h"
#include "PollingStation.h"

#include "Entity.h"
GatherWaterAction::GatherWaterAction(Entity& aEntity)
	: IGOAPAction(aEntity, "GatherWaterAction")
	, myTimer(2.f)
{
	myWaterToGatherFrom = PollingStation::GetInstance()->GetResources(WATER).GetLast();

	myPreConditions.SetState(CAN_GATHER_WATER, true);
	myEffects.SetState(HAS_WATER, true);
}


GatherWaterAction::~GatherWaterAction()
{
}

bool GatherWaterAction::Update(float aDelta)
{
	myTimer -= aDelta;
	if (myTimer <= 0.f)
		return true;

	return false;
}

bool GatherWaterAction::IsInRange()
{
	DL_ASSERT_EXP(myWaterToGatherFrom != nullptr, "Invalid TargetEntity");

	CU::Vector2<float> ownPosition = myEntity.GetPosition();
	CU::Vector2<float> otherPosition = GetTargetPosition();
	CU::Vector2<float> direction = otherPosition - ownPosition;
	float distance = CU::Length(direction);

	if (distance < 10.f)
		return true;

	return false;
}

CU::Vector2<float> GatherWaterAction::GetTargetPosition()
{
	return myWaterToGatherFrom->GetPosition();
}

