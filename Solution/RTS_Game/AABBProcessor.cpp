#include "stdafx.h"
#include "AABBProcessor.h"

#include "AABBComponent.h"
#include "SelectedComponent.h"

#include <Camera.h>

#include <InputWrapper.h>

#include <Intersection.h>
#include <LineSegment3D.h>

AABBProcessor::AABBProcessor(Magma::World& aWorld, const Magma::Camera& aCamera)
	: Magma::BaseProcessor(aWorld, Magma::CreateFilter<Magma::Requires<AABBComponent>>())
	, myCamera(aCamera)
{

}

AABBProcessor::~AABBProcessor()
{
}

void AABBProcessor::Update(float aDelta)
{
	CU::InputWrapper* inputWrapper = CU::InputWrapper::GetInstance();
	if (!inputWrapper->MouseDown(0))
		return;

	CU::Vector2<float> screenPosition = inputWrapper->GetMousePosition();

	CU::Vector3<float> lineStart = Unproject(screenPosition.x, screenPosition.y, 0.f);
	CU::Vector3<float> lineEnd = Unproject(screenPosition.x, screenPosition.y, 1.f);
	CU::Intersection::LineSegment3D lineSeg(lineStart, lineEnd);

	Magma::Entity bestEntity = -1;
	float bestDist = FLT_MAX;
	CU::Vector3f bestIntersectionPoint;

	CU::GrowingArray<Magma::Entity> entities = GetEntities();
	for each (const Magma::Entity& entity in entities)
	{
		AABBComponent& aabbComp = GetComponent<AABBComponent>(entity);

		CU::Vector3<float> temp;
		if (CU::Intersection::LineVsAABB(lineSeg, aabbComp.myAABB, temp))
		{
			float dist = CU::Length2(temp - lineStart);
			if (dist < bestDist)
			{
				bestDist = dist;
				bestEntity = entity;
			}
		}
	}

	if (bestEntity != -1)
	{
		if (!HasComponent<SelectedComponent>(bestEntity))
		{
			AddComponent<SelectedComponent>(bestEntity);
		}
		else
		{
			RemoveComponent<SelectedComponent>(bestEntity);
		}
	}
}

CU::Vector3<float> AABBProcessor::Unproject(float aX, float aY, float aZ)
{
	const CU::Vector2<float> windowSize(1280.f, 720.f);

	float flippedY = windowSize.y - aY;

	CU::Vector4<float> in;
	in.x = aX / windowSize.x * 2.f - 1.f;
	in.y = flippedY / windowSize.y * 2.f - 1.f;
	in.z = 2.f * aZ - 1.f;
	in.w = 1.f;

	CU::Matrix44<float> invertedViewProjection = CU::InverseReal(myCamera.GetView() * myCamera.GetProjection());

	CU::Vector4<float> worldPos = in * invertedViewProjection;
	if (worldPos.w == 0.f)
		return CU::Vector3<float>();

	worldPos.w = 1.f / worldPos.w;

	CU::Vector3<float> out;
	out.x = worldPos.x * worldPos.w;
	out.y = worldPos.y * worldPos.w;
	out.z = worldPos.z * worldPos.w;
	return out;
}
