#include "stdafx.h"

#include "GOAPAction.h"
#include "Entity.h"

void GOAPAction::EndAction()
{
	myEntity.ModifyGOAPState(myEffects);
}
