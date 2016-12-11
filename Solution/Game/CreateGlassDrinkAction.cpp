#include "stdafx.h"
#include "CreateGlassDrinkAction.h"
#include "PollingStation.h"

#include "Entity.h"

CreateGlassDrinkAction::CreateGlassDrinkAction(Entity& aEntity)
	: IGOAPAction(aEntity, "CreateGlassDrinkAction")
	, myTimer(2.f)
{

	myPreConditions.SetState(HAS_WATER, true);
	myPreConditions.SetState(HAS_GLASS, true);
	myEffects.SetState(HAS_DRINK, true);
}


CreateGlassDrinkAction::~CreateGlassDrinkAction()
{
}

bool CreateGlassDrinkAction::Update(float aDelta)
{
	myTimer -= aDelta;
	if (myTimer <= 0.f)
		return true;

	return false;
}

bool CreateGlassDrinkAction::IsInRange()
{
	return true;
}

CU::Vector2<float> CreateGlassDrinkAction::GetTargetPosition()
{
	return myEntity.GetPosition();
}

