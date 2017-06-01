#include "stdafx.h"

#include "DeliverWoodAction.h"
#include "Entity.h"
#include "PollingStation.h"
#include "StockpileComponent.h"

DeliverWoodAction::DeliverWoodAction(Entity& aEntity)
	: GOAPAction(aEntity, "Deliver Wood")
{
	myPreConditions.SetEntityState(eEntityState::HAS_WOOD, true);
	myEffects.SetWorldState(eWorldState::HAS_WOOD_ON_STOCKPILE, true);
	myEffects.SetEntityState(eEntityState::HAS_WOOD, false);
}


DeliverWoodAction::~DeliverWoodAction()
{
}

void DeliverWoodAction::Init()
{
	myStockpileToDeliverTo = PollingStation::GetInstance()->FindFreeStockpile();
}

bool DeliverWoodAction::Update(float /*aDelta*/)
{
	StockpileComponent* stockpile = myStockpileToDeliverTo->GetComponent<StockpileComponent>();
	DL_ASSERT_EXP(stockpile != nullptr, "Tried to Deliver Wood to a non-stockpile entity");

	stockpile->PlaceResource(TREE);

	return true;
}

bool DeliverWoodAction::CheckDynamicCondition()
{
	if (!myStockpileToDeliverTo)
		return false;

	StockpileComponent* stockpile = myStockpileToDeliverTo->GetComponent<StockpileComponent>();
	if (!stockpile)
		return false;

	if (stockpile->IsFull())
		return false;

	return true;
}

bool DeliverWoodAction::IsInRange()
{
	DL_ASSERT_EXP(myStockpileToDeliverTo!= nullptr, "Invalid TargetEntity");

	CU::Vector2<float> ownPosition = myEntity.GetPosition();
	CU::Vector2<float> otherPosition = GetTargetPosition();
	CU::Vector2<float> direction = otherPosition - ownPosition;
	float distance = CU::Length(direction);

	if (distance < 10.f)
		return true;

	return false;
}

CU::Vector2<float> DeliverWoodAction::GetTargetPosition()
{
	return myStockpileToDeliverTo->GetPosition();
}
