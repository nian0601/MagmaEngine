#pragma once
#include "Types.h"
#include "GfxStructs.h"
#include <GrowingArray.h>
#include "GPUData.h"
#include <Matrix.h>
#include <Vector.h>

namespace Magma
{
	class Camera;
	class Effect;
	class GPUContext;
	class TextData;
	class Texture;
	class Renderer;

	class QuadRenderer
	{
	public:
		QuadRenderer(AssetContainer& aAssetContainer, GPUContext& aGPUContext);
		~QuadRenderer();

		void AddSpriteCommand(Texture* aTexture, const CU::Matrix44<float>& aOrientation
			, const CU::Vector4<float>& aSizeAndHotSpot, const CU::Vector4<float>& aPositionAndScale);

		void Activate();

		void RenderSprites(const Camera& aCamera, Renderer& aRenderer);
		void Render(EffectID aEffect, const CU::String& aTechnique);

		void RenderText(TextData* someTextData, const Camera& aCamera, Renderer& aRenderer, const CU::Vector4<float>& aPositionAndScale);

	private:
		void operator=(QuadRenderer&) = delete;

		AssetContainer& myAssetContainer;
		GPUContext& myGPUContext;
		GPUData myGPUData;

		struct SpriteCommand
		{
			SpriteCommand()
			{}
			SpriteCommand(Texture* aTexture, const CU::Matrix44<float>& aOrientation
				, const CU::Vector4<float>& aSizeAndHotSpot
				, const CU::Vector4<float>& aPositionAndScale)
				: myTexture(aTexture)
				, myOrientation(aOrientation)
				, mySizeAndHotSpot(aSizeAndHotSpot)
				, myPositionAndScale(aPositionAndScale)
			{}

			Texture* myTexture;
			CU::Matrix44<float> myOrientation;
			CU::Vector4<float> mySizeAndHotSpot;
			CU::Vector4<float> myPositionAndScale;
		};
		CU::GrowingArray<SpriteCommand> mySpriteCommands;
		EffectID mySpriteEffect;
		EffectVariableID myProjectionVariable;
		EffectVariableID myOrientationVariable;
		EffectVariableID mySizeAndHotSpotVariable;
		EffectVariableID myPosAndScaleVarible;
		EffectVariableID myAlbedoTextureVariable;
	};
}