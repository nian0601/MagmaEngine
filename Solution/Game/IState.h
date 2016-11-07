#pragma once

enum eStateStatus
{
	KEEP_STATE,
	POP_STATE,
};

class Entity;
class FiniteStateMachine;
class IState
{
public:
	virtual ~IState() {}

	virtual eStateStatus Update(float aDelta) = 0;

protected:
	void operator=(IState&) = delete;

	IState(FiniteStateMachine& aStateMachine, Entity& anEntity) 
		: myStateMachine(aStateMachine)
		, myEntity(anEntity)
	{}

	FiniteStateMachine& myStateMachine;
	Entity& myEntity;
};

