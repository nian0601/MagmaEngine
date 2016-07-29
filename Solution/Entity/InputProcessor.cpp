#include "stdafx.h"

#include "InputComponent.h"
#include "InputProcessor.h"
#include "TranslationComponent.h"

#include <InputWrapper.h>

InputProcessor::InputProcessor(World& aWorld)
	: BaseProcessor(aWorld, CreateFilter<Requires<InputComponent, TranslationComponent>>())
{
}


InputProcessor::~InputProcessor()
{
}

void InputProcessor::Update(float aDelta)
{
	CU::InputWrapper* inputWrapper = CU::InputWrapper::GetInstance();

	float speed = 10.f;
	CU::GrowingArray<Entity> entities = GetEntities();
	for each (const Entity& entity in entities)
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
