#include "stdafx.h"
#include "SelectedProcessor.h"

#include "RenderComponent.h"
#include "SelectedComponent.h"

SelectedProcessor::SelectedProcessor(Magma::World& aWorld)
	: Magma::BaseProcessor(aWorld, Magma::CreateFilter<Magma::Requires<SelectedComponent, RenderComponent>>())
{

}

SelectedProcessor::~SelectedProcessor()
{
}

void SelectedProcessor::Update(float aDelta)
{
	CU::GrowingArray<Magma::Entity> entities = GetEntities();
	for each (const Magma::Entity& entity in entities)
	{
		RenderComponent& renderComp = GetComponent<RenderComponent>(entity);
		renderComp.myColor = CU::Vector4<float>(0.f, 1.f, 0.f, 1.f);
	}
}

void SelectedProcessor::EntityRemoved(Magma::Entity aEntity)
{
	if (HasComponent<SelectedComponent>(aEntity))
	{
		RenderComponent& renderComp = GetComponent<RenderComponent>(aEntity);
		renderComp.myColor = CU::Vector4<float>(1.f, 1.f, 1.f, 1.f);
	}
}
