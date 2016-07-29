#pragma once

#include <CUString.h>
#include <Vector.h>
#include <windef.h>
#include <WinUser.h>

#undef CreateWindow

struct ID3D11Device;
struct ID3D11DeviceContext;

namespace CU
{
	class TimerManager;
}

namespace Easy3D
{
	struct Backbuffer;

	class AssetContainer;
	class Camera;
	class DeferredRenderer;
	class DirectX;
	class GPUContext;
	class WindowHandler;
	class IGame;
	class Scene;

	class Engine
	{
	public:
		Engine(const CU::Vector2<float>& aSize, IGame& aGame);
		~Engine();

		void Run();

		GPUContext& GetGPUContext();
		AssetContainer& GetAssetContainer();
		Scene& GetScene();
		Camera& GetCamera();
		const CU::Vector2<float>& GetWindowSize() const;

	private:
		void OnResize();

		IGame& myGame;

		GPUContext* myGPUContext;
		WindowHandler* myWindowHandler;
		AssetContainer* myAssetContainer;
		Scene* myScene;
		DeferredRenderer* myRenderer;
		Camera* myCamera;
		CU::TimerManager* myTimerManager;

		CU::Vector2<float> myWindowSize;
		bool myIsRunning;
	};

	inline GPUContext& Engine::GetGPUContext()
	{
		return *myGPUContext;
	}

	inline AssetContainer& Engine::GetAssetContainer()
	{
		return *myAssetContainer;
	}

	inline const CU::Vector2<float>& Engine::GetWindowSize() const
	{
		return myWindowSize;
	}

	inline Scene& Engine::GetScene()
	{
		return *myScene;
	}

	inline Camera& Engine::GetCamera()
	{
		return *myCamera;
	}
}