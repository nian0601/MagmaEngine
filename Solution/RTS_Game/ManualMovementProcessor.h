#pragma once
#include <Entity/Include/BaseProcessor.h>

class ManualMovementProcessor : public Magma::BaseProcessor
{
public:
	ManualMovementProcessor(Magma::World& aWorld);
	~ManualMovementProcessor();

	void Update(float aDelta) override;
};