#include "stdafx.h"

#include "InputComponent.h"
#include "MovementProcessor.h"
#include "TranslationComponent.h"
#include "MovementTargetComponent.h"

#include <InputWrapper.h>
#include "NavGrid.h"

MovementProcessor::MovementProcessor(Magma::World& aWorld, NavGrid& aNavGrid)
	: Magma::BaseProcessor(aWorld, Magma::CreateFilter<Magma::Requires<MovementTargetComponent, TranslationComponent>>())
	, myNavGrid(aNavGrid)
{
}


MovementProcessor::~MovementProcessor()
{
}

void MovementProcessor::Update(float aDelta)
{
	float speed = 10.f;
	CU::GrowingArray<Magma::Entity> entities = GetEntities();
	for each (const Magma::Entity& entity in entities)
	{
		TranslationComponent& translationComp = GetComponent<TranslationComponent>(entity);
		MovementTargetComponent& targetComp = GetComponent<MovementTargetComponent>(entity);

		if (!targetComp.myHasPath)
			InitPath(entity);

		CU::Vector3f currentPos = translationComp.myOrientation.GetPos();
		CU::Vector3f targetPos = targetComp.myTargetPosition;

		CU::Vector3f diff = targetPos - currentPos;
		float distance = CU::Length(diff);


		if (distance <= 0.5f)
		{
			currentPos = targetPos;

			if (targetComp.myPath.Size() == 0 || !targetComp.myHasPath)
			{
				RemoveComponent<MovementTargetComponent>(entity);
			}
			else
			{
				targetComp.myTargetPosition = targetComp.myPath.GetLast();
				targetComp.myPath.RemoveCyclicAtIndex(targetComp.myPath.Size() - 1);
			}
		}
		else
		{
			CU::Vector3f direction = CU::GetNormalized(diff);
			currentPos += direction * speed * aDelta;
		}

		translationComp.myOrientation.SetPos(currentPos);
	}
}

void MovementProcessor::InitPath(Magma::Entity anEntity)
{
	TranslationComponent& translationComp = GetComponent<TranslationComponent>(anEntity);
	MovementTargetComponent& targetComp = GetComponent<MovementTargetComponent>(anEntity);


	CU::GrowingArray<CU::Vector2f> path;
	if (!myNavGrid.FindPath(translationComp.myOrientation.GetPos(), targetComp.myTargetPosition, path))
	{
		return;
	}

	for (const CU::Vector2f wayPoint : path)
	{
		targetComp.myPath.Add(CU::Vector3f(wayPoint.x, 1.f, wayPoint.y));
	}


	targetComp.myTargetPosition = targetComp.myPath.GetLast();
	targetComp.myPath.RemoveCyclicAtIndex(targetComp.myPath.Size() - 1);
	targetComp.myHasPath = true;

	myNavGrid.BlockCell(targetComp.myPath[0]);
	myNavGrid.UnBlockCell(translationComp.myOrientation.GetPos());
}
