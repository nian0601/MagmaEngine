#pragma once
#include "BaseComponent.h"
#include <EngineTypes.h>

class RenderComponent : public BaseComponent
{
public:
	RenderComponent();
	~RenderComponent();

	Easy3D::ModelID myModelID;
	Easy3D::EffectID myEffectID;
};

