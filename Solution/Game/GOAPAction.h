#pragma once
#include <Vector.h>
#include "GOAPGameState.h"

class Entity;
class GOAPAction
{
public:
	virtual ~GOAPAction() {}

	virtual void Init() = 0;
	void EndAction();

	virtual bool Update(float) = 0;
	virtual bool CheckDynamicCondition() { return true; }

	virtual bool IsInRange() = 0;
	virtual CU::Vector2<float> GetTargetPosition() = 0;
	const GOAPGameState& GetPreConditions() const {	return myPreConditions; }
	const GOAPGameState& GetEffects() const { return myEffects; }

protected:
	void operator=(GOAPAction&) = delete;

	GOAPAction(Entity& aEntity, const CU::String& aDebugName) 
	: myEntity(aEntity)
	, myDebugName(aDebugName)
	{}

	Entity& myEntity;
	GOAPGameState myPreConditions;
	GOAPGameState myEffects;

	CU::String myDebugName;
};