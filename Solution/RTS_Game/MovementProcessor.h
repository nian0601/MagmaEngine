#pragma once
#include <Entity/Include/BaseProcessor.h>

class MovementProcessor : public Magma::BaseProcessor
{
public:
	MovementProcessor(Magma::World& aWorld);
	~MovementProcessor();

	void Update(float aDelta) override;
};