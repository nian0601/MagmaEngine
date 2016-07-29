#include "stdafx.h"

#include "AssetContainer.h"
#include "Camera.h"
#include "Effect.h"
#include "Instance.h"
#include "Renderer.h"

#include <PostMaster.h>
#include <RenderMessage.h>

namespace Easy3D
{
	Instance::Instance(ModelID aModelID, EffectID aEffect)
		: myModelID(aModelID)
		, myEffect(aEffect)
		, myScale(1.f, 1.f, 1.f)
	{
	}


	Instance::~Instance()
	{
	}

	void Instance::Render(Renderer* aRenderer, const Camera& aCamera)
	{
		PostMaster::GetInstance()->SendMessage(RenderMessage(myOrientation, myScale, myModelID, myEffect));

		/*
		aRenderer->SetEffect(myEffect);
		aRenderer->SetMatrix("ViewProjection", aCamera.GetViewProjection());
		aRenderer->SetMatrix("World", myOrientation);
		aRenderer->SetVector("CameraPosition", aCamera.GetPosition());
		aRenderer->SetVector("Scale", myScale);

		aRenderer->RenderModel(myModelID);
		*/
	}

	void Instance::Render()
	{
		PostMaster::GetInstance()->SendMessage(RenderMessage(myOrientation, myScale, myModelID, myEffect));
	}

	void Instance::SetPosition(const CU::Vector3<float>& aPosition)
	{
		myOrientation.SetPos(aPosition);
	}

	CU::Vector3<float> Instance::GetPosition() const
	{
		return myOrientation.GetPos();
	}

	void Instance::SetRotation(const CU::Vector3<float>& aRotation)
	{
		CU::Vector3<float> pos = myOrientation.GetPos();
		myOrientation.SetPos(CU::Vector3<float>());

		myOrientation = myOrientation * CU::Matrix44f::CreateRotateAroundZ(aRotation.z);
		myOrientation = myOrientation * CU::Matrix44f::CreateRotateAroundX(aRotation.x);
		myOrientation = myOrientation * CU::Matrix44f::CreateRotateAroundY(aRotation.y);

		myOrientation.SetPos(pos);
	}

	void Instance::SetScale(const CU::Vector3<float>& aScale)
	{
		myScale = aScale;
	}

}