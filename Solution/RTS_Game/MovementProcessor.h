#pragma once
#include <Entity/Include/BaseProcessor.h>

class NavGrid;
class MovementProcessor : public Magma::BaseProcessor
{
public:
	MovementProcessor(Magma::World& aWorld, NavGrid& aNavGrid);
	~MovementProcessor();

	void Update(float aDelta) override;

private:
	void InitPath(Magma::Entity aEntity);

	NavGrid& myNavGrid;
};