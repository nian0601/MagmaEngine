#include "stdafx.h"
#include "GOAPPlan.h"


GOAPPlan::GOAPPlan(const CU::GrowingArray<IGOAPAction*>& someActions)
	: myActions(someActions)
{
}


GOAPPlan::~GOAPPlan()
{
}

bool GOAPPlan::IsFinished() const
{
	return myActions.Size() == 0;
}

IGOAPAction* GOAPPlan::GetNextAction()
{
	IGOAPAction* action = myActions.GetLast();
	myActions.RemoveCyclicAtIndex(myActions.Size() - 1);

	return action;
}
