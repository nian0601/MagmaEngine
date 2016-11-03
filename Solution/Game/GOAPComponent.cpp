#include "stdafx.h"

#include "Entity.h"
#include "GOAPComponent.h"
#include "PollingStation.h"

#include "FiniteStateMachine.h"
#include "IdleState.h"
#include "MoveToState.h"

GOAPComponent::GOAPComponent(Entity& aEntity)
	: IComponent(aEntity)
	, myTargetEntity(nullptr)
	, myStateMachine(nullptr)
{
}


GOAPComponent::~GOAPComponent()
{
	delete myStateMachine;
	myStateMachine = nullptr;
}

void GOAPComponent::Init(PollingStation* aPollingStation)
{
	myPollingStation = aPollingStation;
	myCurrentResourceType = eResourceType::TREE;

	myTargetEntity = GetClosestEntity(myPollingStation->GetResources(myCurrentResourceType));

	myStateMachine = new FiniteStateMachine(myEntity);
	myStateMachine->PushState<IdleState>();

	Entity* closestTree = GetClosestEntity(myPollingStation->GetResources(TREE));
	Entity* closestWater= GetClosestEntity(myPollingStation->GetResources(WATER));

	MoveToState* moveToWater = myStateMachine->PushState<MoveToState>();
	moveToWater->Init(closestWater);

	MoveToState* moveToTree = myStateMachine->PushState<MoveToState>();
	moveToTree->Init(closestTree);


	MoveToState* moveToWater2 = myStateMachine->PushState<MoveToState>();
	moveToWater2->Init(closestWater);

	MoveToState* moveToTree2 = myStateMachine->PushState<MoveToState>();
	moveToTree2->Init(closestTree);
}

void GOAPComponent::Update(float aDeltaTime)
{
	/*if (!myTargetEntity)
	{
		myTargetEntity = GetClosestEntity(myPollingStation->GetResources(myCurrentResourceType));
		return;
	}

	CU::Vector2<float> ownPosition = myEntity.GetPosition();
	CU::Vector2<float> otherPosition = myTargetEntity->GetPosition();
	CU::Vector2<float> direction = otherPosition - ownPosition;
	float distance = CU::Length(direction);
	CU::Normalize(direction);

	ownPosition += direction * 100.f * aDeltaTime;

	if (distance < 10.f)
	{
		ownPosition = myTargetEntity->GetPosition();
		switch (myCurrentResourceType)
		{
			case TREE: myCurrentResourceType = WATER; break;
			case WATER: myCurrentResourceType = TREE; break;
		}

		myTargetEntity = GetClosestEntity(myPollingStation->GetResources(myCurrentResourceType));
	}
	myEntity.SetPosition(ownPosition);*/

	myStateMachine->Update(aDeltaTime);
}

Entity* GOAPComponent::GetClosestEntity(const CU::GrowingArray<Entity*>& someEntities) const
{
	CU::Vector2<float> ownPosition = myEntity.GetPosition();

	float bestDist = FLT_MAX;
	Entity* bestEntity = nullptr;

	for (int i = 0; i < someEntities.Size(); ++i)
	{
		CU::Vector2<float> otherPosition = someEntities[i]->GetPosition();

		CU::Vector2<float> vec = ownPosition - otherPosition;
		float dist = CU::Length2(vec);

		if (dist < bestDist)
		{
			bestDist = dist;
			bestEntity = someEntities[i];
		}
	}

	return bestEntity;
}
