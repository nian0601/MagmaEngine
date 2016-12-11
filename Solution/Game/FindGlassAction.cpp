#include "stdafx.h"
#include "FindGlassAction.h"
#include "PollingStation.h"

#include "Entity.h"

FindGlassAction::FindGlassAction(Entity& aEntity)
	: IGOAPAction(aEntity, "FindGlassAction")
	, myTimer(2.f)
{

	myEffects.SetState(HAS_GLASS, true);
}


FindGlassAction::~FindGlassAction()
{
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

