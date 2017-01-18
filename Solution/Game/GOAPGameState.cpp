#include "stdafx.h"
#include "GOAPGameState.h"


GOAPGameState::GOAPGameState()
{
	for (int i = 0; i < static_cast<int>(eEntityState::_COUNT); ++i)
		myEntityState[i] = 0;

	for (int i = 0; i < static_cast<int>(eWorldState::_COUNT); ++i)
		myWorldState[i] = 0;
}


GOAPGameState::~GOAPGameState()
{
}

void GOAPGameState::SetEntityState(eEntityState aState, bool aStatus)
{
	char& stateStatus = InternalGetState(aState);

	if (aStatus)
		stateStatus = 1;
	else
		stateStatus = -1;
}

void GOAPGameState::SetEntityState(const GOAPGameState& aGOAPState)
{
	for (int i = 0; i < static_cast<int>(eEntityState::_COUNT); ++i)
		myEntityState[i] = aGOAPState.myEntityState[i];
}

void GOAPGameState::ResetEntityState(eEntityState aState)
{
	char& stateStatus = InternalGetState(aState);
	stateStatus = 0.f;
}

bool GOAPGameState::GetEntityState(eEntityState aState) const
{
	char stateStatus = InternalGetState(aState);

	if (stateStatus == 1)
		return true;
	
	return false;
}

bool GOAPGameState::IsEntityStateSet(eEntityState aState) const
{
	char stateStatus = InternalGetState(aState);

	if (stateStatus == 0)
		return false;
	
	return true;
}

void GOAPGameState::SetWorldState(eWorldState aState, bool aStatus)
{
	char& stateStatus = InternalGetState(aState);

	if (aStatus)
		stateStatus = 1;
	else
		stateStatus = -1;
}

void GOAPGameState::SetWorldState(const GOAPGameState& aGOAPState)
{
	for (int i = 0; i < static_cast<int>(eEntityState::_COUNT); ++i)
		myWorldState[i] = aGOAPState.myWorldState[i];
}

void GOAPGameState::ResetWorldState(eWorldState aState)
{
	char& stateStatus = InternalGetState(aState);
	stateStatus = 0.f;
}

bool GOAPGameState::GetWorldState(eWorldState aState) const
{
	char stateStatus = InternalGetState(aState);

	if (stateStatus == 1)
		return true;

	return false;
}

bool GOAPGameState::IsWorldStateSet(eWorldState aState) const
{
	char stateStatus = InternalGetState(aState);

	if (stateStatus == 0)
		return false;

	return true;
}

bool GOAPGameState::Contains(const GOAPGameState& aState) const
{
	for (int i = 0; i < static_cast<int>(eEntityState::_COUNT); ++i)
	{
		eEntityState entityState = static_cast<eEntityState>(i);
		if (aState.IsEntityStateSet(entityState))
		{
			if (aState.myEntityState[i] != myEntityState[i])
				return false;
		}
	}

	for (int i = 0; i < static_cast<int>(eWorldState::_COUNT); ++i)
	{
		eWorldState worldState = static_cast<eWorldState>(i);
		if (aState.IsWorldStateSet(worldState))
		{
			if (aState.myWorldState[i] != myWorldState[i])
				return false;
		}
	}

	return true;
}

void GOAPGameState::GetNewState(const GOAPGameState& someEffects, GOAPGameState& anOutState) const
{
	anOutState = *this;
	for (int i = 0; i < static_cast<int>(eEntityState::_COUNT); ++i)
	{
		eEntityState state = static_cast<eEntityState>(i);
		if (someEffects.IsEntityStateSet(state))
			anOutState.SetEntityState(state, someEffects.GetEntityState(state));
	}

	for (int i = 0; i < static_cast<int>(eWorldState::_COUNT); ++i)
	{
		eWorldState state = static_cast<eWorldState>(i);
		if (someEffects.IsWorldStateSet(state))
			anOutState.SetWorldState(state, someEffects.GetWorldState(state));
	}
}

void GOAPGameState::GetNewEntityState(const GOAPGameState& someEffects, GOAPGameState& anOutState) const
{
	anOutState = *this;
	for (int i = 0; i < static_cast<int>(eEntityState::_COUNT); ++i)
	{
		eEntityState state = static_cast<eEntityState>(i);
		if (someEffects.IsEntityStateSet(state))
			anOutState.SetEntityState(state, someEffects.GetEntityState(state));
	}
}

void GOAPGameState::GetNewWorldState(const GOAPGameState& someEffects, GOAPGameState& anOutState) const
{
	anOutState = *this;
	for (int i = 0; i < static_cast<int>(eWorldState::_COUNT); ++i)
	{
		eWorldState state = static_cast<eWorldState>(i);
		if (someEffects.IsWorldStateSet(state))
			anOutState.SetWorldState(state, someEffects.GetWorldState(state));
	}
}

char& GOAPGameState::InternalGetState(eEntityState aState)
{
	DL_ASSERT_EXP(static_cast<int>(aState) >= 0 && aState < eEntityState::_COUNT, "Invalid EntityState");
	return myEntityState[static_cast<int>(aState)];
}

const char& GOAPGameState::InternalGetState(eEntityState aState) const
{
	DL_ASSERT_EXP(static_cast<int>(aState) >= 0 && aState < eEntityState::_COUNT, "Invalid EntityState");
	return myEntityState[static_cast<int>(aState)];
}

const char& GOAPGameState::InternalGetState(eWorldState aState) const
{
	DL_ASSERT_EXP(static_cast<int>(aState) >= 0 && aState < eWorldState::_COUNT, "Invalid WorldState");
	return myWorldState[static_cast<int>(aState)];
}

char& GOAPGameState::InternalGetState(eWorldState aState)
{
	DL_ASSERT_EXP(static_cast<int>(aState) >= 0 && aState < eWorldState::_COUNT, "Invalid WorldState");
	return myWorldState[static_cast<int>(aState)];
}
