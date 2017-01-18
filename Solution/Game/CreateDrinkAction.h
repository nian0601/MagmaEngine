#pragma once

#include "GOAPAction.h"

class Entity;
class CreateDrinkAction : public GOAPAction
{
public:
	CreateDrinkAction(Entity& aEntity);
	~CreateDrinkAction();

	virtual void Init() override;
	virtual bool Update(float aDelta) override;
	virtual bool IsInRange() override;
	virtual CU::Vector2<float> GetTargetPosition() override;

private:
	void operator=(CreateDrinkAction&) = delete;

	float myTimer;
};
