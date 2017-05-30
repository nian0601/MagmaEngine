#pragma once

#include <Entity/Include/BaseProcessor.h>

class AABBProcessor : public Magma::BaseProcessor
{
public:
	AABBProcessor(Magma::World& aWorld);
	~AABBProcessor();

	void Update(float aDelta) override;
};

