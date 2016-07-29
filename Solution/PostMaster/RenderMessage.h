#pragma once
#include "Message.h"
#include <EngineTypes.h>
#include <Matrix.h>
#include <Vector.h>

struct RenderMessage : public Message
{
	RenderMessage();

	RenderMessage(const CU::Matrix44<float>& aOrientation, const CU::Vector3<float>& aScale
		, Easy3D::ModelID aModelID, Easy3D::EffectID aEffectID);

	CU::Matrix44<float> myOrientation;
	CU::Vector3<float> myScale;
	Easy3D::ModelID myModelID;
	Easy3D::EffectID myEffectID;
};

inline RenderMessage::RenderMessage()
	: Message(eMessageType::RENDER)
{
}

inline RenderMessage::RenderMessage(const CU::Matrix44<float>& aOrientation, const CU::Vector3<float>& aScale
		, Easy3D::ModelID aModelID, Easy3D::EffectID aEffectID)
	: Message(eMessageType::RENDER)
	, myOrientation(aOrientation)
	, myScale(aScale)
	, myModelID(aModelID)
	, myEffectID(aEffectID)
{
}