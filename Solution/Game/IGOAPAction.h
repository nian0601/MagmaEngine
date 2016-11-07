#pragma once
#include <Vector.h>

class Entity;
class IGOAPAction
{
public:
	virtual ~IGOAPAction() {}

	virtual bool Update(float) = 0;

	virtual bool IsInRange() = 0;
	virtual CU::Vector2<float> GetTargetPosition() = 0;

protected:
	void operator=(IGOAPAction&) = delete;

	IGOAPAction(Entity& aEntity) 
	: myEntity(aEntity)
	{}

	Entity& myEntity;
};