#pragma once
#include <CUMap.h>
#include <CUString.h>
#include "EngineTypes.h"
#include <GrowingArray.h>
#include <Vector.h>

namespace std
{
	class thread;
}

namespace Easy3D
{
	class Effect;
	class GPUContext;
	class Instance;
	class IModelFactory;
	class ModelData;
	class Texture;

	class AssetContainer
	{
	public:
		AssetContainer(GPUContext& aGPUContext);
		~AssetContainer();

		Instance* CreateInstance(const CU::String<64>& aModelPath, const CU::String<64>& aEffectPath);
		ModelID LoadModel(const CU::String<64>& aModelPath, const CU::String<64>& aEffectPath);
		ModelData* GetModel(ModelID aID);

		EffectID LoadEffect(const CU::String<64>& aFilePath);
		Effect* GetEffect(EffectID aID);

		Texture* RequestTexture(const CU::String<64>& aFilePath);

	private:
		void Run();

		IModelFactory* myModelFactory;

		CU::Map<EffectID, Effect*> myEffects;
		CU::Map<CU::String<64>, EffectID> myEffectsID;
		EffectID myNextEffectID;

		CU::Map<ModelID, ModelData*> myModels;
		CU::Map<CU::String<64>, ModelID> myModelID;
		ModelID myNextModelID;

		CU::Map<CU::String<64>, Texture*> myTextures;

		GPUContext& myGpuContext;
		static AssetContainer* myInstance;
	};
}