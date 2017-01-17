#pragma once
#include <CUMap.h>
#include <CUString.h>
#include "Types.h"
#include <GrowingArray.h>
#include <Vector.h>

namespace std
{
	class thread;
}

namespace Magma
{
	class Effect;
	class GPUContext;
	class IModelFactory;
	class ModelData;
	class Texture;

	class AssetContainer
	{
	public:
		AssetContainer(GPUContext& aGPUContext);
		~AssetContainer();

		ModelID LoadModel(const CU::String& aModelPath, const CU::String& aEffectPath);
		ModelData* GetModel(ModelID aID);

		EffectID LoadEffect(const CU::String& aFilePath);
		Effect* GetEffect(EffectID aID);

		EffectVariableID CreateEffectVariableID(EffectID aEffect, const CU::String& aVariableName);
		const CU::String& GetEffectVariableName(EffectID aEffect, EffectVariableID aVariableID);

		Texture* LoadTexture(const CU::String& aFilePath);

	private:
		void operator=(AssetContainer&) = delete;

		void Run();

		IModelFactory* myModelFactory;

		CU::Map<EffectID, Effect*> myEffects;
		CU::Map<CU::String, EffectID> myEffectsID;
		EffectID myNextEffectID;

		CU::Map<EffectID, CU::Map<EffectVariableID, CU::String>> myEffectVariables;
		EffectVariableID myNextEffectVariableID;

		CU::Map<ModelID, ModelData*> myModels;
		CU::Map<CU::String, ModelID> myModelID;
		ModelID myNextModelID;

		CU::Map<CU::String, Texture*> myTextures;

		GPUContext& myGpuContext;
		static AssetContainer* myInstance;
	};
}