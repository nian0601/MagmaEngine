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
			AABB(const CU::Vector3<float>& aPosition, const CU::Vector3<float>& aScale)
				: myCenterPos(aPosition)
				, myExtents(aScale)
				, myMinPos(aPosition - aScale * 0.5f)
				, myMaxPos(aPosition + aScale * 0.5f)
			{}
			void InitWithTwoPoints(const CU::Vector3<float>& aMinPosition, const CU::Vector3<float>& aMaxPosition)
			{
				myMinPos = aMinPosition;
				myMaxPos = aMaxPosition;
				myCenterPos = (myMinPos + myMaxPos) * 0.5f;
				myExtents = myMaxPos - myMinPos;
			}
			void Transform(const CU::Matrix44<float>& aMatrix)
			{
				CU::Vector4<float> minPos(myMinPos.x, myMinPos.y, myMinPos.z, 1.f);
				CU::Vector4<float> maxPos(myMaxPos.x, myMaxPos.y, myMaxPos.z, 1.f);

				minPos = minPos * aMatrix;
				maxPos = maxPos * aMatrix;

				InitWithTwoPoints(CU::Vector3f(minPos.x, minPos.y, minPos.z), CU::Vector3f(maxPos.x, maxPos.y, maxPos.z));
			}

			CU::Vector3<float> myCenterPos;
			CU::Vector3<float> myExtents;
			CU::Vector3<float> myMinPos;
			CU::Vector3<float> myMaxPos;
		};
	}
}