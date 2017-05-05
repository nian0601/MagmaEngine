#pragma once

#include "IModelFactory.h"
#include "GfxStructs.h"
#include <GrowingArray.h>
#include <CUMap.h>

struct D3D11_INPUT_ELEMENT_DESC;

namespace FBX
{
	struct AnimationData;
	struct Bone;
	struct ModelData;

	class FBXLoader;
	class FbxModelData;
}

namespace Magma
{
	class AssetContainer;
	class ModelData;
	class GPUData;
	class Texture;

	class FBXFactory : public IModelFactory
	{
	public:
		FBXFactory(AssetContainer& aAssetContainer, GPUContext& aGPUContext);
		~FBXFactory();

		ModelData* LoadModel(const CU::String& aFilePath, EffectID aEffect) override;
		ModelData* LoadCube(EffectID aEffect) override;
		
	private:
		void operator=(FBXFactory&) = delete;

		ModelData* CreateModel(FBX::FbxModelData* someModelData);
		void LoadData(GPUData& someGPUData, FBX::ModelData* someFBXData);

		AssetContainer& myAssetContainer;
		GPUContext& myGPUContext;

		FBX::FBXLoader *myLoader;
		CU::Map<CU::String, ModelData*> myModels;
		ModelData* myCubeModelData;
	};
}