#include "stdafx.h"
#include "BaseProcessor.h"
#include "World.h"

BaseProcessor::BaseProcessor(World& aWorld)
	: myWorld(aWorld)
{
}


BaseProcessor::BaseProcessor(World& aWorld, const ComponentFilter& aFilter)
	: myWorld(aWorld)
	, myComponentFilter(aFilter)
{

}

BaseProcessor::~BaseProcessor()
{
}

const CU::GrowingArray<Entity>& BaseProcessor::GetEntities()
{
	return myWorld.GetEntities(myComponentFilter);
}
