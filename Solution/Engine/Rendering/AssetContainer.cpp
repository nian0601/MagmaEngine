#include "stdafx.h"
#include "AssetContainer.h"
#include "Effect.h"
#include "FBXFactory.h"
#include "Texture.h"

namespace Magma
{
	ModelID AssetContainer::LoadModel(const CU::String& aModelPath, const CU::String& aEffectPath)
	{
		EffectID effect = LoadEffect(aEffectPath);

		if (myModelID.KeyExists(aModelPath) == false)
		{
			ModelData* modelData = myModelFactory->LoadModel(aModelPath, effect);

			myModels[myNextModelID] = modelData;
			myModelID[aModelPath] = myNextModelID;
			++myNextModelID;
		}

		return myModelID[aModelPath];
	}

	Magma::ModelData* AssetContainer::GetModel(ModelID aID)
	{
		if (myModels.KeyExists(aID) == true)
		{
			return myModels[aID];
		}

		DL_ASSERT("Tried to Get an Invalid model");
		return nullptr;
	}

	EffectID AssetContainer::LoadEffect(const CU::String& aFilePath)
	{
		if (myEffectsID.KeyExists(aFilePath) == false)
		{
			Effect* effect = new Effect();
			effect->Init(aFilePath, myGpuContext);

			myEffects[myNextEffectID] = effect;
			myEffectsID[aFilePath] = myNextEffectID;
			++myNextEffectID;
		}

		return myEffectsID[aFilePath];
	}

	Effect* AssetContainer::GetEffect(EffectID aID)
	{
		if (myEffects.KeyExists(aID) == true)
		{
			return myEffects[aID];
		}

		DL_ASSERT("Tried to Get an Invalid effect");
		return nullptr;
	}

	Magma::EffectVariableID AssetContainer::CreateEffectVariableID(EffectID aEffect, const CU::String& aVariableName)
	{
		EffectVariableID currentID = myNextEffectVariableID;
		++myNextEffectVariableID;

		myEffectVariables[aEffect][currentID] = aVariableName;
		return currentID;
	}

	const CU::String& AssetContainer::GetEffectVariableName(EffectID aEffect, EffectVariableID aVariableID)
	{
		if (!myEffectVariables.KeyExists(aEffect))
		{
			DL_ASSERT("Tried to GetEffectVariableName from invalid Effect");
			return "";
		}

		if (!myEffectVariables[aEffect].KeyExists(aVariableID))
		{
			DL_ASSERT("Tried to GetEffectVariableName from invalid VariableID, did you forget to CreateEffectVariableID?");
			return "";
		}

		return myEffectVariables[aEffect][aVariableID];
	}

	Texture* AssetContainer::LoadTexture(const CU::String& aFilePath)
	{
		if (myTextures.KeyExists(aFilePath) == false)
		{
			Texture* newTex = new Texture();
			newTex->LoadTexture(aFilePath, myGpuContext);
			myTextures[aFilePath] = newTex;
		}

		return myTextures[aFilePath];
	}

	AssetContainer::AssetContainer(GPUContext& aGPUContext)
		: myGpuContext(aGPUContext)
	{
		myModelFactory = new FBXFactory(*this, myGpuContext);
	}


	AssetContainer::~AssetContainer()
	{
		SAFE_DELETE(myModelFactory);

		for (auto it = myEffects.Begin(); it != myEffects.End(); it = myEffects.Next(it))
		{
			SAFE_DELETE(it.Second());
		}
		myEffects.Clear();

		for (auto it = myTextures.Begin(); it != myTextures.End(); it = myTextures.Next(it))
		{
			SAFE_DELETE(it.Second());
		}
		myTextures.Clear();
	}
}