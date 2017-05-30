#include "stdafx.h"

#include "InputComponent.h"
#include "ManualMovementProcessor.h"
#include "TranslationComponent.h"
#include "SelectedComponent.h"
#include "MovementTargetComponent.h"

#include <InputWrapper.h>

ManualMovementProcessor::ManualMovementProcessor(Magma::World& aWorld)
	: Magma::BaseProcessor(aWorld, Magma::CreateFilter<Magma::Requires<MovementTargetComponent, TranslationComponent>>())
{
}


ManualMovementProcessor::~ManualMovementProcessor()
{
}

void ManualMovementProcessor::Update(float aDelta)
{
	CU::InputWrapper* inputWrapper = CU::InputWrapper::GetInstance();

	float speed = 10.f;
	CU::GrowingArray<Magma::Entity> entities = GetEntities();
	for each (const Magma::Entity& entity in entities)
	{
		TranslationComponent& translation = GetComponent<TranslationComponent>(entity);

		CU::Vector3<float> pos = translation.myOrientation.GetPos();
		if (inputWrapper->KeyIsPressed(DIK_W))
		{
			pos.z += speed * aDelta;
		}
		else if (inputWrapper->KeyIsPressed(DIK_S))
		{
			pos.z -= speed * aDelta;
		}
		else if (inputWrapper->KeyIsPressed(DIK_A))
		{
			pos.x -= speed * aDelta;
		}
		else if (inputWrapper->KeyIsPressed(DIK_D))
		{
			pos.x += speed * aDelta;
		}
		else if (inputWrapper->KeyIsPressed(DIK_Q))
		{
			pos.y -= speed * aDelta;
		}
		else if (inputWrapper->KeyIsPressed(DIK_E))
		{
			pos.y += speed * aDelta;
		}

		translation.myOrientation.SetPos(pos);
	}
}
