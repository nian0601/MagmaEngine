#pragma once

#include <Entity/Include/BaseComponent.h>
#include <AABB.h>

class AABBComponent : public Magma::BaseComponent
{
public:
	AABBComponent();
	~AABBComponent();


	CU::Intersection::AABB myAABB;
};

