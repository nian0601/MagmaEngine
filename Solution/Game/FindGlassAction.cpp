#include "stdafx.h"
#include "FindGlassAction.h"
#include "PollingStation.h"

#include "Entity.h"

FindGlassAction::FindGlassAction(Entity& aEntity)
	: GOAPAction(aEntity, "FindGlassAction")
{
	myEffects.SetEntityState(eEntityState::HAS_GLASS, true);
}


FindGlassAction::~FindGlassAction()
{
}

void FindGlassAction::Init()
{
	myTimer = 2.f;
}

bool FindGlassAction::Update(float aDelta)
{
	myTimer -= aDelta;
	if (myTimer <= 0.f)
		return true;

	return false;
}

bool FindGlassAction::IsInRange()
{
	return true;
}

CU::Vector2<float> FindGlassAction::GetTargetPosition()
{
	return myEntity.GetPosition();
}

