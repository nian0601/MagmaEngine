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


	mySpriteTexture = aEngine.GetAssetContainer().RequestTexture("Data/Resource/Texture/T_background_nightmare.dds");
}

bool Game::Update(float aDelta)
{
	CU::InputWrapper* input = CU::InputWrapper::GetInstance();

	if (input->KeyIsPressed(DIK_ESCAPE))
	{
		return false;
	}

	myRendererProxy->RenderSprite(mySpriteTexture, mySpriteOrientation, { 2048, 1024, 0, 0 }, { 4, 4, 0.5, 0.5 });

	return true;
}

void Game::OnResize(float aWidth, float aHeight)
{
	//throw std::logic_error("The method or operation is not implemented.");
}