#pragma once
#include <Entity/Include/BaseComponent.h>
#include <Types.h>

class RenderComponent : public Magma::BaseComponent
{
public:
	RenderComponent();
	~RenderComponent();

	Magma::ModelID myModelID;
	Magma::EffectID myEffectID;
	CU::Vector4<float> myColor;
	CU::Vector4<float> myOriginalColor;
};

