#pragma once

#include "GOAPAction.h"

class Entity;
class FindGlassAction : public GOAPAction
{
public:
	FindGlassAction(Entity& aEntity);
	~FindGlassAction();

	virtual void Init() override;
	virtual bool Update(float aDelta) override;
	virtual bool IsInRange() override;
	virtual CU::Vector2<float> GetTargetPosition() override;

private:
	void operator=(FindGlassAction&) = delete;

	float myTimer;
};
