#include "stdafx.h"
#include "GOAPPlan.h"
#include "GOAPAction.h"

GOAPPlan::GOAPPlan(const CU::GrowingArray<GOAPAction*>& someActions)
	: myActions(someActions)
	, myCurrentAction(nullptr)
{
}


GOAPPlan::~GOAPPlan()
{
}

bool GOAPPlan::CheckDynamicCondition()
{
	if (myCurrentAction)
		return myCurrentAction->CheckDynamicCondition();

	return false;
}

bool GOAPPlan::IsFinished() const
{
	return myActions.Size() == 0;
}

GOAPAction* GOAPPlan::GetNextAction()
{
	myCurrentAction = myActions.GetLast();
	myActions.RemoveCyclicAtIndex(myActions.Size() - 1);

	return myCurrentAction;
}
