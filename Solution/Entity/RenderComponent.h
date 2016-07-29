#pragma once
#include "BaseComponent.h"
#include <EngineTypes.h>

class RenderComponent : public BaseComponent
{
public:
	RenderComponent();
	~RenderComponent();

	Magma::ModelID myModelID;
	Magma::EffectID myEffectID;
};

