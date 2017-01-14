#pragma once

#include "IGOAPAction.h"

class Entity;
class GatherWaterAction : public IGOAPAction
{
public:
	GatherWaterAction(Entity& aEntity);
	~GatherWaterAction();

	virtual void Init() override;
	virtual bool Update(float aDelta) override;
	virtual bool IsInRange() override;
	virtual CU::Vector2<float> GetTargetPosition() override;

private:
	void operator=(GatherWaterAction&) = delete;

	Entity* myWaterToGatherFrom;
	float myTimer;
};
