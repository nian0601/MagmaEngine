#pragma once

#include <Entity/Include/BaseProcessor.h>

class HighlightingProcessor : public Magma::BaseProcessor
{
public:
	HighlightingProcessor(Magma::World& aWorld);
	~HighlightingProcessor();

	void Update(float aDelta) override;
	void EntityRemoved(Magma::Entity aEntity) override;
};

