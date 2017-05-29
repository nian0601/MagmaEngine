#include "stdafx.h"

#include "TranslationComponent.h"
#include "RenderComponent.h"
#include "RenderProcessor.h"

#include "PostMaster.h"
#include "RenderMessage.h"

RenderProcessor::RenderProcessor(Magma::World& aWorld)
	: Magma::BaseProcessor(aWorld, Magma::CreateFilter<Magma::Requires<TranslationComponent, RenderComponent>>())
{
}


RenderProcessor::~RenderProcessor()
{
}

void RenderProcessor::Update(float aDelta)
{
	CU::GrowingArray<Magma::Entity> entities = GetEntities();
	for each (const Magma::Entity& entity in entities)
	{
		TranslationComponent& translation = GetComponent<TranslationComponent>(entity);
		RenderComponent& render = GetComponent<RenderComponent>(entity);

		CU::Vector4<float> color(0.f, 1.f, 0.f, 1.f);
		PostMaster::GetInstance()->SendMessage(RenderMessage(translation.myOrientation, color, translation.myScale, render.myModelID, render.myEffectID));
	}
}
