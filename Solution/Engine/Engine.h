#pragma once

#include <CUString.h>
#include <Vector.h>
#include <windef.h>
#include <WinUser.h>

namespace CU
{
	class TimerManager;
}

namespace Magma
{
	class AssetContainer;
	class Camera;
	class DeferredRenderer;
	class GPUContext;
	class WindowHandler;
	class IGame;
	class Renderer;
	class RendererProxy;

	class Engine
	{
	public:
		Engine(const CU::Vector2<float>& aSize, IGame& aGame);
		~Engine();

		void Run();

		GPUContext& GetGPUContext();
		AssetContainer& GetAssetContainer();
		Camera& GetCamera();
		RendererProxy& GetRendererProxy();
		const CU::Vector2<float>& GetWindowSize() const;

	private:
		void operator=(Engine&) = delete;

		void Update();
		void Render();

		void OnResize();

		IGame& myGame;

		GPUContext* myGPUContext;
		WindowHandler* myWindowHandler;
		AssetContainer* myAssetContainer;
		Camera* myCamera;

		Renderer* myRenderer;
		RendererProxy* myRendererProxy;
		DeferredRenderer* myDeferredRenderer;
		CU::TimerManager* myTimerManager;

		CU::Vector2<float> myWindowSize;
		bool myIsRunning;


		int FPS;
		float DT;
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

	inline Camera& Engine::GetCamera()
	{
		return *myCamera;
	}

	inline RendererProxy& Engine::GetRendererProxy()
	{
		return *myRendererProxy;
	}
}