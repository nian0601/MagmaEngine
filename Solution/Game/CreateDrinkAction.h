#pragma once

#include "IGOAPAction.h"

class Entity;
class CreateDrinkAction : public IGOAPAction
{
public:
	CreateDrinkAction(Entity& aEntity);
	~CreateDrinkAction();

	virtual bool Update(float aDelta) override;
	virtual bool IsInRange() override;
	virtual CU::Vector2<float> GetTargetPosition() override;

private:
	void operator=(CreateDrinkAction&) = delete;

	float myTimer;
};
