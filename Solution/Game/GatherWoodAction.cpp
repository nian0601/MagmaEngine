#include "stdafx.h"
#include "GatherWoodAction.h"
#include "PollingStation.h"

#include "Entity.h"
GatherWoodAction::GatherWoodAction(Entity& aEntity)
	: IGOAPAction(aEntity)
	, myTimer(2.f)
{
	myTreeToGatherFrom = PollingStation::GetInstance()->GetResources(TREE).GetLast();
}


GatherWoodAction::~GatherWoodAction()
{
}

bool GatherWoodAction::Update(float aDelta)
{
	myTimer -= aDelta;
	if (myTimer <= 0.f)
		return true;

	return false;
}

bool GatherWoodAction::IsInRange()
{
	DL_ASSERT_EXP(myTreeToGatherFrom != nullptr, "Invalid TargetEntity");

	CU::Vector2<float> ownPosition = myEntity.GetPosition();
	CU::Vector2<float> otherPosition = GetTargetPosition();
	CU::Vector2<float> direction = otherPosition - ownPosition;
	float distance = CU::Length(direction);

	if (distance < 10.f)
		return true;

	return false;
}

CU::Vector2<float> GatherWoodAction::GetTargetPosition()
{
	return myTreeToGatherFrom->GetPosition();
}
