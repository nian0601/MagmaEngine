#include "stdafx.h"
#include "AABBProcessor.h"

#include "AABBComponent.h"
#include "TranslationComponent.h"

AABBProcessor::AABBProcessor(Magma::World& aWorld)
	: Magma::BaseProcessor(aWorld, Magma::CreateFilter<Magma::Requires<AABBComponent, TranslationComponent>>())
{
}


AABBProcessor::~AABBProcessor()
{
}

void AABBProcessor::Update(float /*aDelta*/)
{
	CU::GrowingArray<Magma::Entity> entities = GetEntities();
	for each (const Magma::Entity& entity in entities)
	{
		TranslationComponent& translationComp = GetComponent<TranslationComponent>(entity);
		AABBComponent& aabbComp = GetComponent<AABBComponent>(entity);

		aabbComp.myAABB.InitWithPointAndExtents(translationComp.myOrientation.GetPos(), translationComp.myScale);
	}
}
