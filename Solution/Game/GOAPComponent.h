#pragma once

#include "IComponent.h"
#include "EntityDefines.h"

class FiniteStateMachine;
class IGOAPAction;

class GOAPComponent : public IComponent
{
public:
	GOAPComponent(Entity& aEntity);
	~GOAPComponent();

	void Init();

	virtual void Update(float) override;

private:
	eResourceType myCurrentResourceType;

	FiniteStateMachine* myStateMachine;

	CU::GrowingArray<IGOAPAction*> myActions;
};

