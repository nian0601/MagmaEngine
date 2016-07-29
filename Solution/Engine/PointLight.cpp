#include "stdafx.h"

#include "Instance.h"
#include "PointLight.h"


namespace Easy3D
{
	PointLight::PointLight(const CU::Vector3<float>& aPosition, const CU::Vector4<float>& aColor, float aRange)
	{
		myData.myPosition = CU::Vector4<float>(aPosition, 1.f);
		myData.myColor = aColor;
		myData.myRange = aRange;
	}


	PointLight::~PointLight()
	{
	}
}