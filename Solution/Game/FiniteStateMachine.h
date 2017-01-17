#pragma once

#include <GrowingArray.h>

class IState;
class Entity;
class FiniteStateMachine
{
public:
	FiniteStateMachine(Entity& anEntity);
	~FiniteStateMachine();

	bool Update(float aDelta);

	template <typename T>
	T* PushState();

	void PopAll();

private:
	void operator=(FiniteStateMachine&) = delete;

	Entity& myEntity;
	CU::GrowingArray<IState*> myStates;
};

template <typename T>
T* FiniteStateMachine::PushState()
{
	T* newState = new T(*this, myEntity);
	myStates.Add(newState);

	return newState;
}

