#include "stdafx.h"

#include "TranslationComponent.h"
#include "RenderComponent.h"
#include "RenderProcessor.h"

#include <PostMaster.h>
#include <RenderMessage.h>

RenderProcessor::RenderProcessor(World& aWorld)
	: BaseProcessor(aWorld, CreateFilter<Requires<TranslationComponent, RenderComponent>>())
{
}


RenderProcessor::~RenderProcessor()
{
}

void RenderProcessor::Update(float aDelta)
{
	CU::GrowingArray<Entity> entities = GetEntities();
	for each (const Entity& entity in entities)
	{
		TranslationComponent& translation = GetComponent<TranslationComponent>(entity);
		RenderComponent& render = GetComponent<RenderComponent>(entity);

		PostMaster::GetInstance()->SendMessage(RenderMessage(translation.myOrientation, translation.myScale, render.myModelID, render.myEffectID));
	}
}
