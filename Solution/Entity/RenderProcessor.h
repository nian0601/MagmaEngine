#pragma once
#include "BaseProcessor.h"

class RenderProcessor : public BaseProcessor
{
public:
	RenderProcessor(World& aWorld);
	~RenderProcessor();

	void Update(float aDelta) override;
};

