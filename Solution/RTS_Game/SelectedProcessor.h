#pragma once

#include <Entity/Include/BaseProcessor.h>

class SelectedProcessor : public Magma::BaseProcessor
{
public:
	SelectedProcessor(Magma::World& aWorld);
	~SelectedProcessor();

	void Update(float aDelta) override;
	void EntityRemoved(Magma::Entity aEntity) override;
};

