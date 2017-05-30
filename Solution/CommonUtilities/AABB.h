#pragma once
#include "Vector.h"
#include "Matrix.h"
namespace CU
{
	namespace Intersection
	{
		struct AABB
		{
			AABB()
			{}
			AABB(const CU::Vector3<float>& aPosition, const CU::Vector3<float>& aExtents)
			{
				InitWithPointAndExtents(aPosition, aExtents);
			}
			void InitWithPointAndExtents(const CU::Vector3<float>& aPosition, const CU::Vector3<float>& aExtents)
			{
				myCenterPos = aPosition;
				myExtents = aExtents;
				myMinPos = aPosition - aExtents * 0.5f;
				myMaxPos = aPosition + aExtents * 0.5f;
			}
			void InitWithTwoPoints(const CU::Vector3<float>& aMinPosition, const CU::Vector3<float>& aMaxPosition)
			{
				myMinPos = aMinPosition;
				myMaxPos = aMaxPosition;
				myCenterPos = (myMinPos + myMaxPos) * 0.5f;
				myExtents = myMaxPos - myMinPos;
			}

			CU::Vector3<float> myCenterPos;
			CU::Vector3<float> myExtents;
			CU::Vector3<float> myMinPos;
			CU::Vector3<float> myMaxPos;
		};
	}
}