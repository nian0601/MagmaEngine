#pragma once
#include "EngineTypes.h"
#include "GfxStructs.h"
#include <GrowingArray.h>
#include "GPUData.h"

namespace Magma
{
	class Effect;
	class GPUContext;

	class FullscreenQuad
	{
	public:
		FullscreenQuad(AssetContainer& aAssetContainer, GPUContext& aGPUContext);
		~FullscreenQuad();

		void Activate();
		void Render(EffectID aEffect, const CU::String<30>& aTechnique);

	private:
		void operator=(FullscreenQuad&) = delete;

		AssetContainer& myAssetContainer;
		GPUContext& myGPUContext;
		GPUData myGPUData;
	};
}