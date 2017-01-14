#include "stdafx.h"

#include "DeliverWaterAction.h"
#include "Entity.h"
#include "PollingStation.h"
#include "StockpileComponent.h"

DeliverWaterAction::DeliverWaterAction(Entity& aEntity)
	: IGOAPAction(aEntity, "Deliver Water")
{
	myPreConditions.SetState(HAS_WATER, true);
	myEffects.SetState(HAS_WATER_ON_STOCKPILE, true);
}


DeliverWaterAction::~DeliverWaterAction()
{
}

void DeliverWaterAction::Init()
{
	myStockpileToDeliverTo = PollingStation::GetInstance()->FindFreeStockpile();
}

bool DeliverWaterAction::Update(float aDelta)
{
	StockpileComponent* stockpile = myStockpileToDeliverTo->GetComponent<StockpileComponent>();
	DL_ASSERT_EXP(stockpile, "Tried to Deliver Water to a non-stockpile entity");

	stockpile->PlaceResource(WATER);

	return true;
}

bool DeliverWaterAction::IsInRange()
{
	DL_ASSERT_EXP(myStockpileToDeliverTo != nullptr, "Invalid TargetEntity");

	CU::Vector2<float> ownPosition = myEntity.GetPosition();
	CU::Vector2<float> otherPosition = GetTargetPosition();
	CU::Vector2<float> direction = otherPosition - ownPosition;
	float distance = CU::Length(direction);

	if (distance < 10.f)
		return true;

	return false;
}

CU::Vector2<float> DeliverWaterAction::GetTargetPosition()
{
	return myStockpileToDeliverTo->GetPosition();
}
