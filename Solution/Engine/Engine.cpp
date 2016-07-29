#include "stdafx.h"

#include "AssetContainer.h"
#include "Camera.h"
#include "DeferredRenderer.h"
#include "Engine.h"
#include "GPUContext.h"
#include "IGame.h"
#include <InputWrapper.h>
#include "Scene.h"
#include <TimerManager.h>
#include "WindowHandler.h"

namespace Easy3D
{
	Engine::Engine(const CU::Vector2<float>& aSize, IGame& aGame)
		: myGPUContext(nullptr)
		, myWindowSize(aSize)
		, myGame(aGame)
	{
		myWindowHandler = new WindowHandler(myWindowSize);
		myGPUContext = new GPUContext(myWindowSize, myWindowHandler->GetHwnd());
		myAssetContainer = new AssetContainer(*myGPUContext);

		myRenderer = new DeferredRenderer(*myAssetContainer, *myGPUContext, myWindowSize);

		myCamera = new Camera();
		myCamera->Resize(myWindowSize);
		myScene = new Scene();
		myScene->SetCamera(*myCamera);

		myTimerManager = new CU::TimerManager();

		CU::InputWrapper::Create(myWindowHandler->GetHwnd(), GetModuleHandle(NULL), DISCL_NONEXCLUSIVE
			| DISCL_FOREGROUND, DISCL_NONEXCLUSIVE | DISCL_FOREGROUND);

		myGame.Init(*this);
	}


	Engine::~Engine()
	{
		SAFE_DELETE(myWindowHandler);
		SAFE_DELETE(myGPUContext);
		SAFE_DELETE(myAssetContainer);
		SAFE_DELETE(myRenderer);
		SAFE_DELETE(myCamera);
		SAFE_DELETE(myScene);
		SAFE_DELETE(myTimerManager)
		DL_Debug::Debug::Destroy();
		CU::InputWrapper::Destroy();
	}

	void Engine::Run()
	{
		myIsRunning = true;
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

				myTimerManager->Update();
				CU::InputWrapper::GetInstance()->Update();

				myIsRunning = myGame.Update(myTimerManager->GetMasterTimer().GetTime().GetFrameTime());

				myRenderer->Render(myScene);
				myGPUContext->FinishFrame();

				myTimerManager->CapFrameRate(60.f);
			}
		}
	}

	void Engine::OnResize()
	{
		myRenderer->Resize(myWindowSize.x, myWindowSize.y);
		myCamera->Resize(myWindowSize);
	}

}