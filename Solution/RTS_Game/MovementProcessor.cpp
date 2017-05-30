#include "stdafx.h"

#include "InputComponent.h"
#include "MovementProcessor.h"
#include "TranslationComponent.h"
#include "MovementTargetComponent.h"

#include <InputWrapper.h>

MovementProcessor::MovementProcessor(Magma::World& aWorld)
	: Magma::BaseProcessor(aWorld, Magma::CreateFilter<Magma::Requires<MovementTargetComponent, TranslationComponent>>())
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

		CU::Vector3f currentPos = translationComp.myOrientation.GetPos();
		CU::Vector3f targetPos = targetComp.myTargetPosition;

		CU::Vector3f diff = targetPos - currentPos;
		float distance = CU::Length(diff);


		if (distance <= 0.5f)
		{
			currentPos = targetPos;
			RemoveComponent<MovementTargetComponent>(entity);
		}
		else
		{
			CU::Vector3f direction = CU::GetNormalized(diff);
			currentPos += direction * speed * aDelta;
		}

		translationComp.myOrientation.SetPos(currentPos);
	}
}
