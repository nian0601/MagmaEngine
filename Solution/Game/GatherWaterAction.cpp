#include "stdafx.h"
#include "GatherWaterAction.h"
#include "PollingStation.h"
#include "GatheringComponent.h"
#include "Entity.h"

GatherWaterAction::GatherWaterAction(Entity& aEntity)
	: IGOAPAction(aEntity, "GatherWaterAction")
{
	myPreConditions.SetState(CAN_GATHER_WATER, true);
	myEffects.SetState(HAS_WATER, true);
}


GatherWaterAction::~GatherWaterAction()
{
}

void GatherWaterAction::Init()
{
	myWaterToGatherFrom = PollingStation::GetInstance()->GetResources(WATER).GetLast();
	myTimer = 2.f;
}

bool GatherWaterAction::Update(float aDelta)
{
	myTimer -= aDelta;
	if (myTimer <= 0.f)
	{
		GatheringComponent* gatherComp = myEntity.GetComponent<GatheringComponent>();
		if (gatherComp)
			gatherComp->SetResourceType(WATER);

		return true;
	}

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

