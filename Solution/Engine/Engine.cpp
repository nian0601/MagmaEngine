#include "stdafx.h"

#include "AssetContainer.h"
#include "Camera.h"
#include "DeferredRenderer.h"
#include "Engine.h"
#include "GPUContext.h"
#include "IGame.h"
#include <InputWrapper.h>
#include "Renderer.h"
#include "RendererProxy.h"
#include <TimerManager.h>
#include "WindowHandler.h"

#include "DebugDrawer.h"
#include "Profiler.h"

namespace Magma
{
	Engine::Engine(const CU::Vector2<float>& aSize, IGame& aGame)
		: myGPUContext(nullptr)
		, myWindowSize(aSize)
		, myGame(aGame)
	{
		myWindowHandler = new WindowHandler(myWindowSize);
		myGPUContext = new GPUContext(myWindowSize, myWindowHandler->GetHwnd());
		myAssetContainer = new AssetContainer(*myGPUContext);

		myRenderer = new Renderer(*myAssetContainer, *myGPUContext);
		myRendererProxy = new RendererProxy(*myRenderer);
		myRenderer->SetClearColor({ 0.1f, 0.1f, 0.1f, 1.f });
		myDeferredRenderer = new DeferredRenderer(*myAssetContainer, *myGPUContext
			, *myRenderer, myWindowSize);

		myCamera = new Camera();
		myCamera->Resize(myWindowSize);

		myTimerManager = new CU::TimerManager();

		CU::InputWrapper::Create(myWindowHandler->GetHwnd(), GetModuleHandle(NULL), DISCL_NONEXCLUSIVE
			| DISCL_FOREGROUND, DISCL_NONEXCLUSIVE | DISCL_FOREGROUND);

		DebugDrawer::GetInstance();
		Profiler::GetInstance()->Init(*myAssetContainer);
		myGame.Init(*this);		
	}


	Engine::~Engine()
	{
		SAFE_DELETE(myTimerManager);
		SAFE_DELETE(myCamera);
		SAFE_DELETE(myDeferredRenderer);
		SAFE_DELETE(myRendererProxy);
		SAFE_DELETE(myRenderer);
		SAFE_DELETE(myAssetContainer);
		SAFE_DELETE(myGPUContext);
		SAFE_DELETE(myWindowHandler);
		Profiler::Destroy();
		DebugDrawer::GetInstance()->Destroy();
		DL_Debug::Debug::Destroy();
		CU::InputWrapper::Destroy();
	}

	void Engine::Run()
	{
		myIsRunning = true;
		CU::String windowTitle;
		while (myIsRunning == true)
		{
			if (myWindowHandler->PumpEvent() == false)
			{
				myIsRunning = false;
			}
			else
			{
				if (myWindowHandler->GetShouldResize() == true)
				{
					myWindowHandler->HasResized();
					myWindowSize = myWindowHandler->GetNewSize();

					//OnResize();
					myGame.OnResize(myWindowSize.x, myWindowSize.y);
				}

				{
					PROFILE_START("Engine: Update");
					myTimerManager->Update();

					{
						PROFILE_START("Input");
						CU::InputWrapper::GetInstance()->Update();
						PROFILE_END();
					}

					myAssetContainer->FlushFileWatcher();

					float deltaTime = myTimerManager->GetFrameTime();

					FPS = static_cast<int>(1.f / deltaTime);
					DT = deltaTime * 1000.f;
					DEBUG_PRINT(FPS);
					DEBUG_PRINT(DT);


					myIsRunning = myGame.Update(deltaTime);

					PROFILE_END();
				}

				{
					PROFILE_START("Engine: Render");
					myDeferredRenderer->Render(*myCamera);
					myRenderer->RenderSprites(*myCamera);
					myRenderer->RenderText(*myCamera);
					myGPUContext->FinishFrame();
					PROFILE_END();
				}

				Profiler::GetInstance()->Render(*myRendererProxy);
				Profiler::GetInstance()->EndFrame();

				DebugDrawer::GetInstance()->ClearDebugTexts();
				//myTimerManager->CapFrameRate(60.f);
			}
		}
	}

	void Engine::OnResize()
	{
		myDeferredRenderer->Resize(myWindowSize.x, myWindowSize.y);
		myCamera->Resize(myWindowSize);
	}

}