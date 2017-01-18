#pragma once

class GOAPAction;

class GOAPPlan
{
public:
	GOAPPlan(const CU::GrowingArray<GOAPAction*>& someActions);
	~GOAPPlan();

	bool CheckDynamicCondition();
	bool IsFinished() const;
	GOAPAction* GetNextAction();

private:
	CU::GrowingArray<GOAPAction*> myActions;
	GOAPAction* myCurrentAction;
};

