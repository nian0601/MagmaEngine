#pragma once

#include "GOAPAction.h"

class Entity;
class GatherWoodAction : public GOAPAction
{
public:
	GatherWoodAction(Entity& aEntity);
	~GatherWoodAction();

	virtual void Init() override;
	virtual bool Update(float aDelta) override;
	virtual bool IsInRange() override;
	virtual CU::Vector2<float> GetTargetPosition() override;

private:
	void operator=(GatherWoodAction&) = delete;

	Entity* myTreeToGatherFrom;
	float myTimer;
};

