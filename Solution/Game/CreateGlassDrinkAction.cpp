#include "stdafx.h"
#include "CreateGlassDrinkAction.h"
#include "PollingStation.h"

#include "Entity.h"

CreateGlassDrinkAction::CreateGlassDrinkAction(Entity& aEntity)
	: IGOAPAction(aEntity, "CreateGlassDrinkAction")
{
	myPreConditions.SetState(HAS_WATER, true);
	myPreConditions.SetState(HAS_GLASS, true);
	myEffects.SetState(HAS_DRINK, true);
}


CreateGlassDrinkAction::~CreateGlassDrinkAction()
{
}

void CreateGlassDrinkAction::Init()
{
	myTimer = 2.f;
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

