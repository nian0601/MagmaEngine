#include "stdafx.h"

#include <CommonHelper.h>
#include <d3dx11effect.h>
#include <D3D10effect.h>
#include <D3DX11async.h>
#include <D3Dcompiler.h>
#include "Effect.h"
#include "GPUContext.h"
#include "Texture.h"

namespace Magma
{
	Effect::Effect()
		: myEffect(nullptr)
		, myFileName("NOT INITIALIZED")
	{
	}

	Effect::~Effect()
	{
		SAFE_RELEASE(myEffect);
	}

	void Effect::Init(const CU::String& aFilePath, GPUContext& aGPUContext)
	{
		Sleep(100);
		myFileName = CU::GetFileNameFromFilePath(aFilePath);
		myFilePath = aFilePath;

		unsigned int shaderFlags = 0;
#ifdef _DEBUG
		shaderFlags |= D3D10_SHADER_DEBUG | D3D10_SHADER_SKIP_OPTIMIZATION;
#endif

		ID3D10Blob* compiledShader = nullptr;
		ID3D10Blob* compilerMsg = nullptr;

		HRESULT result = D3DX11CompileFromFile(myFilePath.c_str(), 0, 0, 0, "fx_5_0", shaderFlags, 0, 0, &compiledShader, &compilerMsg, 0);

		if (FAILED(result))
		{
			CU::String errorMessage = "";

			if (compilerMsg != nullptr)
			{
				DL_MESSAGE_BOX((char*)compilerMsg->GetBufferPointer(), "Effect Error", MB_ICONWARNING);

				errorMessage = "[Effect]: Failed to compile";
			}
			else
			{
				errorMessage = "[Effect]: Could not find the effect ";
				errorMessage += myFileName.c_str();
			}

			DL_ASSERT(errorMessage.c_str());
		}

		if (compilerMsg)
		{
			SAFE_RELEASE(compilerMsg);
		}

		

		result = D3DX11CreateEffectFromMemory(compiledShader->GetBufferPointer(), compiledShader->GetBufferSize(), NULL, aGPUContext.GetDevice(), &myEffect);
		DL_ASSERT_EXP(SUCCEEDED(result) == TRUE, "Failed to Create shader");

		if (compiledShader)
		{
			SAFE_RELEASE(compiledShader);
		}
	}

	void Effect::ReloadShader(const CU::String& aFilePath, GPUContext& aGPUContext)
	{
		if (myEffect) SAFE_RELEASE(myEffect);

		Init(aFilePath, aGPUContext);
	}

	ID3DX11Effect* Effect::GetEffect() const
	{
		return myEffect;
	}

	ID3DX11EffectTechnique* Effect::GetTechnique(const CU::String& aTechniqueName) const
	{
		return myEffect->GetTechniqueByName(aTechniqueName.c_str());
	}
}