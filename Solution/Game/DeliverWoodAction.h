#pragma once

#include "GOAPAction.h"

class Entity;
class DeliverWoodAction : public GOAPAction
{
public:
	DeliverWoodAction(Entity& aEntity);
	~DeliverWoodAction();

	virtual void Init() override;
	virtual bool Update(float aDelta) override;
	virtual bool CheckDynamicCondition() override;

	virtual bool IsInRange() override;
	virtual CU::Vector2<float> GetTargetPosition() override;

private:
	void operator=(DeliverWoodAction&) = delete;

	Entity* myStockpileToDeliverTo;
};
