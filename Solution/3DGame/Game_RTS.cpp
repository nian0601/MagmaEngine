#include "stdafx.h"

#include "Game_RTS.h"
#include <windows.h>
#include <Engine.h>
#include <AssetContainer.h>

#include <Matrix.h>
#include <RendererProxy.h>
#include <Camera.h>

Game_RTS::Game_RTS()
{
}


Game_RTS::~Game_RTS()
{
}

void Game_RTS::Init(Magma::Engine& aEngine)
{
	myCamera = &aEngine.GetCamera();
	myCamera->Move({ 0.f, 0.f, -10.f });

	/*myModelID = aEngine.GetAssetContainer().LoadModel("Data/Resource/Model/blenderbox.fbx", "Data/Resource/Shader/S_effect_cube.fx");
	myEffectID = aEngine.GetAssetContainer().LoadEffect("Data/Resource/Shader/S_effect_cube.fx");*/

	myModelID = aEngine.GetAssetContainer().LoadCube("Data/Resource/Shader/S_effect_simple_cube.fx");
	myEffectID = aEngine.GetAssetContainer().LoadEffect("Data/Resource/Shader/S_effect_simple_cube.fx");

	myRendererProxy = &aEngine.GetRendererProxy();
}

bool Game_RTS::Update(float aDelta)
{
	myCamera->Update();
	aDelta;
	
	int apa = 5;
	++apa;

	CU::Matrix44<float> orientation;
	orientation.SetPos({ 0.f, 0.f, 0.f });
	myRendererProxy->RenderModel(myModelID, myEffectID, orientation);
	

	return true;
}

void Game_RTS::OnResize(float aWidth, float aHeight)
{
	aWidth;
	aHeight;
}
