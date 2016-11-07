#pragma once

#include "IGOAPAction.h"

class Entity;
class GatherWaterAction : public IGOAPAction
{
public:
	GatherWaterAction(Entity& aEntity);
	~GatherWaterAction();

	virtual bool Update(float aDelta) override;
	virtual bool IsInRange() override;
	virtual CU::Vector2<float> GetTargetPosition() override;

private:
	void operator=(GatherWaterAction&) = delete;

	Entity* myTreeToGatherFrom;
	float myTimer;
};

