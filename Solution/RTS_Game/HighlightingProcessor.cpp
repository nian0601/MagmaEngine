#include "stdafx.h"
#include "HighlightingProcessor.h"

#include "RenderComponent.h"
#include "SelectedComponent.h"

HighlightingProcessor::HighlightingProcessor(Magma::World& aWorld)
	: Magma::BaseProcessor(aWorld, Magma::CreateFilter<Magma::Requires<SelectedComponent, RenderComponent>>())
{

}

HighlightingProcessor::~HighlightingProcessor()
{
}

void HighlightingProcessor::Update(float /*aDelta*/)
{
	CU::GrowingArray<Magma::Entity> entities = GetEntities();
	for each (const Magma::Entity& entity in entities)
	{
		RenderComponent& renderComp = GetComponent<RenderComponent>(entity);
		renderComp.myColor = CU::Vector4<float>(0.f, 1.f, 0.f, 1.f);
	}
}

void HighlightingProcessor::EntityRemoved(Magma::Entity aEntity)
{
	if (HasComponent<SelectedComponent>(aEntity))
	{
		RenderComponent& renderComp = GetComponent<RenderComponent>(aEntity);
		renderComp.myColor = renderComp.myOriginalColor;
	}
}
