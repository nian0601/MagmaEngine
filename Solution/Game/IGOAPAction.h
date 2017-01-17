#pragma once
#include <Vector.h>
#include "GOAPGameState.h"

class Entity;
class IGOAPAction
{
public:
	virtual ~IGOAPAction() {}

	virtual void Init() = 0;

	virtual bool Update(float) = 0;
	virtual bool CheckDynamicCondition() { return true; }

	virtual bool IsInRange() = 0;
	virtual CU::Vector2<float> GetTargetPosition() = 0;
	virtual const GOAPGameState& GetPreConditions() const {	return myPreConditions; }
	virtual const GOAPGameState& GetEffects() const { return myEffects; }

protected:
	void operator=(IGOAPAction&) = delete;

	IGOAPAction(Entity& aEntity, const CU::String& aDebugName) 
	: myEntity(aEntity)
	, myDebugName(aDebugName)
	{}

	Entity& myEntity;
	GOAPGameState myPreConditions;
	GOAPGameState myEffects;

	CU::String myDebugName;
};