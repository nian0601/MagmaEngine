#pragma once
#include "BaseComponent.h"
#include <Matrix.h>
#include <Vector.h>

class TranslationComponent : public BaseComponent
{
public:
	TranslationComponent();
	~TranslationComponent();

	CU::Matrix44<float> myOrientation;
	CU::Vector3<float> myScale;
};

