#pragma once
#include "Message.h"
#include <Types.h>
#include <Matrix.h>
#include <Vector.h>

struct RenderMessage : public Message
{
	RenderMessage();

	RenderMessage(const CU::Matrix44<float>& aOrientation, const CU::Vector4<float>& aColor, const CU::Vector3<float>& aScale
		, Magma::ModelID aModelID, Magma::EffectID aEffectID);

	CU::Matrix44<float> myOrientation;
	CU::Vector4<float> myColor;
	CU::Vector3<float> myScale;
	Magma::ModelID myModelID;
	Magma::EffectID myEffectID;
};

inline RenderMessage::RenderMessage()
	: Message(eMessageType::RENDER)
{
}

inline RenderMessage::RenderMessage(const CU::Matrix44<float>& aOrientation, const CU::Vector4<float>& aColor, const CU::Vector3<float>& aScale
		, Magma::ModelID aModelID, Magma::EffectID aEffectID)
	: Message(eMessageType::RENDER)
	, myOrientation(aOrientation)
	, myColor(aColor)
	, myScale(aScale)
	, myModelID(aModelID)
	, myEffectID(aEffectID)
{
}