#pragma once

#include "EntityDefines.h"
#include "StaticArray.h"

class GOAPGameState
{
public:
	GOAPGameState();
	~GOAPGameState();

	void SetEntityState(const GOAPGameState& aGOAPState);
	void SetEntityState(eEntityState aState, bool aStatus);
	void ResetEntityState(eEntityState aState);
	bool GetEntityState(eEntityState aState) const;
	bool IsEntityStateSet(eEntityState aState) const;

	void SetWorldState(const GOAPGameState& aGOAPState);
	void SetWorldState(eWorldState aState, bool aStatus);
	void ResetWorldState(eWorldState aState);
	bool GetWorldState(eWorldState aState) const;
	bool IsWorldStateSet(eWorldState aState) const;

	bool Contains(const GOAPGameState& aState) const;

	void GetNewState(const GOAPGameState& someEffects, GOAPGameState& anOutState) const;
	void GetNewEntityState(const GOAPGameState& someEffects, GOAPGameState& anOutState) const;
	void GetNewWorldState(const GOAPGameState& someEffects, GOAPGameState& anOutState) const;

private:
	char& InternalGetState(eEntityState aState);
	const char& InternalGetState(eEntityState aState) const;

	char& InternalGetState(eWorldState aState);
	const char& InternalGetState(eWorldState aState) const;

	CU::StaticArray<char, static_cast<int>(eEntityState::_COUNT)> myEntityState;
	CU::StaticArray<char, static_cast<int>(eWorldState::_COUNT)> myWorldState;
};

