#pragma once

#include "GOAPAction.h"

class Entity;
class CreateGlassDrinkAction : public GOAPAction
{
public:
	CreateGlassDrinkAction(Entity& aEntity);
	~CreateGlassDrinkAction();

	virtual void Init() override;
	virtual bool Update(float aDelta) override;
	virtual bool IsInRange() override;
	virtual CU::Vector2<float> GetTargetPosition() override;

private:
	void operator=(CreateGlassDrinkAction&) = delete;

	float myTimer;
};
