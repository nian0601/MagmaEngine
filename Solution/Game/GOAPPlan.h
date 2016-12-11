#pragma once

class IGOAPAction;

class GOAPPlan
{
public:
	GOAPPlan(const CU::GrowingArray<IGOAPAction*>& someActions);
	~GOAPPlan();

	bool IsFinished() const;
	IGOAPAction* GetNextAction();

private:
	CU::GrowingArray<IGOAPAction*> myActions;
};

