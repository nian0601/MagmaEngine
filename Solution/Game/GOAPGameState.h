#pragma once

#include "EntityDefines.h"
#include "StaticArray.h"

class GOAPGameState
{
public:
	GOAPGameState();
	~GOAPGameState();

	void SetState(eEntityState aState, bool aStatus);
	void ResetState(eEntityState aState);
	bool GetState(eEntityState aState) const;
	bool IsSet(eEntityState aState) const;

	bool Contains(const GOAPGameState& aState) const;

	void GetNewState(const GOAPGameState& someEffects, GOAPGameState& anOutState) const;

private:
	void SetState(eEntityState aState, char aStatus);

	CU::StaticArray<char, eEntityState::_STATE_COUNT> myState;
};

