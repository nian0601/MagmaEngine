#include "stdafx.h"

#include "IComponent.h"
#include "Entity.h"

Entity::Entity()
{
	for (int i = 0; i < myMaxNumComponents; ++i)
		myComponents[i] = nullptr;
}


Entity::~Entity()
{
	for (int i = 0; i < myMaxNumComponents; ++i)
	{
		delete myComponents[i];
		myComponents[i] = nullptr;
	}
}

void Entity::Update(float aDelta)
{
	for (int i = 0; i < myMaxNumComponents; ++i)
	{
		if (IComponent* comp = myComponents[i])
			comp->Update(aDelta);
	}
}

void Entity::Render(Magma::RendererProxy& aRendererProxy)
{
	for (int i = 0; i < myMaxNumComponents; ++i)
	{
		if (IComponent* comp = myComponents[i])
			comp->Render(aRendererProxy);
	}
}

CU::Vector2<float> Entity::GetPosition() const
{
	return myOrientation.GetPos();
}

void Entity::SetPosition(const CU::Vector2<float>& aPosition)
{
	myOrientation.SetPos(aPosition);
}
