#pragma once

#include <CUString.h>
#include <Matrix.h>

struct ID3DX11Effect;
struct ID3DX11EffectTechnique;
struct ID3DX11EffectMatrixVariable;
struct ID3DX11EffectShaderResourceVariable;
struct ID3DX11EffectVectorVariable;
struct ID3DX11EffectScalarVariable;

struct ID3D11ShaderResourceView;

namespace Magma
{
	class GPUContext;
	class Texture;

	class Effect
	{
	public:
		Effect();
		~Effect();

		void Init(const CU::String& aFilePath, GPUContext& aGPUContext);
		void ReloadShader(const CU::String& aFilePath, GPUContext& aGPUContext);

		ID3DX11Effect* GetEffect() const;
		ID3DX11EffectTechnique* GetTechnique(const CU::String& aTechniqueName) const;

	private:
		ID3DX11Effect* myEffect;
		CU::String myFileName;
		CU::String myFilePath;
	};
}