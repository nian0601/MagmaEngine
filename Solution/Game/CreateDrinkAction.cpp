#include "stdafx.h"
#include "CreateDrinkAction.h"
#include "PollingStation.h"

#include "Entity.h"

CreateDrinkAction::CreateDrinkAction(Entity& aEntity)
	: GOAPAction(aEntity, "CreateDrinkAction")
{
	myPreConditions.SetEntityState(eEntityState::HAS_WATER, true);
	myEffects.SetEntityState(eEntityState::HAS_DRINK, true);
}


CreateDrinkAction::~CreateDrinkAction()
{
}

void CreateDrinkAction::Init()
{
	myTimer = 2.f;
}

bool CreateDrinkAction::Update(float aDelta)
{
	myTimer -= aDelta;
	if (myTimer <= 0.f)
	{
		myEntity.SetPosition({ 500.f, 20.f });
		return true;
	}

	return false;
}

bool CreateDrinkAction::IsInRange()
{
	return true;
}

CU::Vector2<float> CreateDrinkAction::GetTargetPosition()
{
	return myEntity.GetPosition();
}

