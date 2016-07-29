#include "stdafx.h"

#include <Rendering/AssetContainer.h>
#include <Rendering/Camera.h>
#include <Engine.h>
#include "Game.h"
#include <Rendering/RendererProxy.h>

Game::Game()
{
}


Game::~Game()
{
}

void Game::Init(Magma::Engine& aEngine)
{
	myCamera = &aEngine.GetCamera();
	myCamera->Move({ 0.f, 0.f, -30.f });

	myRendererProxy = &aEngine.GetRendererProxy();
}

bool Game::Update(float aDelta)
{
	CU::InputWrapper* input = CU::InputWrapper::GetInstance();

	if (input->KeyIsPressed(DIK_ESCAPE))
	{
		return false;
	}

	return true;
}

void Game::OnResize(float aWidth, float aHeight)
{
	//throw std::logic_error("The method or operation is not implemented.");
}