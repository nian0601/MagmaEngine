#pragma once
#include <Vector.h>

struct ID3D11Device;
struct ID3D11DeviceContext;

namespace Easy3D
{
	struct Backbuffer;

	class DirectX;
	class GPUContext
	{
	public:
		GPUContext(const CU::Vector2<float>& aScreenSize, const HWND& aHwnd);
		~GPUContext();

		void FinishFrame();

		ID3D11Device* GetDevice() const;
		ID3D11DeviceContext* GetContext() const;

		void SetBackbufferAsRenderTarget();
		void GetBackbuffer(Backbuffer& aBackbufferOut);

	private:
		DirectX* myDirectX;
	};
}