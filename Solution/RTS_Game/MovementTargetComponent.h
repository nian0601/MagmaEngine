#pragma once
#include <Entity/Include/BaseComponent.h>

class MovementTargetComponent : public Magma::BaseComponent
{
public:
	MovementTargetComponent();
	~MovementTargetComponent();

	CU::Vector3f myTargetPosition;
};

