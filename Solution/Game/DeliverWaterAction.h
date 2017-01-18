#pragma once

#include "GOAPAction.h"

class Entity;
class DeliverWaterAction : public GOAPAction
{
public:
	DeliverWaterAction(Entity& aEntity);
	~DeliverWaterAction();

	virtual void Init() override;
	virtual bool Update(float aDelta) override;
	virtual bool CheckDynamicCondition() override;

	virtual bool IsInRange() override;
	virtual CU::Vector2<float> GetTargetPosition() override;

private:
	void operator=(DeliverWaterAction&) = delete;

	Entity* myStockpileToDeliverTo;
};
