#pragma once

#include <GrowingArray.h>
#include <Matrix.h>
#include "EngineTypes.h"

namespace Easy3D
{
	class GPUContext;
	class GPUData;

	class ModelData
	{
		friend class FBXFactory;
		friend class Renderer;
	public:
		ModelData();
		~ModelData();

		void Init(EffectID aEffectID, GPUContext& aGPUContext, AssetContainer& aAssetContainer);
		void AddChild(ModelData* aModelData);

	private:
		GPUData* myGPUData;

		CU::GrowingArray<ModelData*> myChildren;
		CU::GrowingArray<CU::Matrix44<float>> myChildTransforms;
		CU::Matrix44<float> myOrientation;
		bool myIsNullObject;
	};

	struct ModelBatchData
	{
		ModelData myModelData;
		CU::GrowingArray<CU::Matrix44<float>> myOrientations;
	};
}