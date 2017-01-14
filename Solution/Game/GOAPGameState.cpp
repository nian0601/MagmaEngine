#include "stdafx.h"
#include "GOAPGameState.h"


GOAPGameState::GOAPGameState()
{
	for (int i = 0; i < eEntityState::_STATE_COUNT; ++i)
		myState[i] = 0;
}


GOAPGameState::~GOAPGameState()
{
}

void GOAPGameState::SetState(eEntityState aState, bool aStatus)
{
	DL_ASSERT_EXP(aState >= 0 && aState < eEntityState::_STATE_COUNT, "Invalid EntityState");
	char& stateStatus = myState[aState];

	if (aStatus)
		stateStatus = 1;
	else
		stateStatus = -1;
}

void GOAPGameState::ResetState(eEntityState aState)
{
	DL_ASSERT_EXP(aState >= 0 && aState < eEntityState::_STATE_COUNT, "Invalid EntityState");
	myState[aState] = 0.f;
}

bool GOAPGameState::GetState(eEntityState aState) const
{
	DL_ASSERT_EXP(aState >= 0 && aState < eEntityState::_STATE_COUNT, "Invalid EntityState");
	char stateStatus = myState[aState];

	if (stateStatus == 1)
		return true;
	
	return false;
}

bool GOAPGameState::IsSet(eEntityState aState) const
{
	DL_ASSERT_EXP(aState >= 0 && aState < eEntityState::_STATE_COUNT, "Invalid EntityState");
	char stateStatus = myState[aState];

	if (stateStatus == 0)
		return false;
	
	return true;
}

bool GOAPGameState::Contains(const GOAPGameState& aState) const
{
	for (int i = 0; i < eEntityState::_STATE_COUNT; ++i)
	{
		eEntityState entityState = static_cast<eEntityState>(i);
		if (aState.IsSet(entityState))
		{
			if (aState.myState[i] != myState[i])
				return false;
		}
	}

	return true;
}

void GOAPGameState::GetNewState(const GOAPGameState& someEffects, GOAPGameState& anOutState) const
{
	anOutState = *this;
	for (int i = 0; i < eEntityState::_STATE_COUNT; ++i)
	{
		eEntityState state = static_cast<eEntityState>(i);
		if (someEffects.IsSet(state))
			anOutState.SetState(state, someEffects.GetState(state));
	}
}

void GOAPGameState::SetState(eEntityState aState, char aStatus)
{
	DL_ASSERT_EXP(aState >= 0 && aState < eEntityState::_STATE_COUNT, "Invalid EntityState");
	myState[aState] = aStatus;
}