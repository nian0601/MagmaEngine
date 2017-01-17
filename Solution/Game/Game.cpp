#include "stdafx.h"

#include <Rendering/AssetContainer.h>
#include <Rendering/Camera.h>
#include <Engine.h>
#include "Game.h"
#include <Rendering/RendererProxy.h>


#include "Entity.h"
#include "SpriteComponent.h"
#include "ResourceComponent.h"
#include "GOAPComponent.h"
#include "StockpileComponent.h"

#include "PollingStation.h"

Game::Game()
{
}


Game::~Game()
{
	PollingStation::Destroy();
	myEntities.DeleteAll();
}

void Game::Init(Magma::Engine& aEngine)
{
	myCamera = &aEngine.GetCamera();
	myCamera->Move({ 0.f, 0.f, -30.f });

	myRendererProxy = &aEngine.GetRendererProxy();
	myAssetContainer = &aEngine.GetAssetContainer();

	myEntities.Init(128);

	for (int x = 0; x < 10; ++x)
	{
		for (int y = 0; y < 10; ++y)
		{
			Entity* entity = new Entity();

			SpriteComponent* sprite = entity->AddComponent<SpriteComponent>();
			sprite->Init(*myAssetContainer, "Data/Resource/Texture/T_ground.dds", { 32.f, 32.f });

			CU::Vector2<float> pos;
			pos.x = 128.f + x * (32.f + 1.f);
			pos.y = 128.f + y * (32.f + 1.f);

			entity->SetPosition(pos);

			myEntities.Add(entity);
		}
	}

	for (int x = 6; x < 9; ++x)
	{
		for (int y = 6; y < 9; ++y)
		{
			Entity* entity = new Entity();

			SpriteComponent* sprite = entity->AddComponent<SpriteComponent>();
			sprite->Init(*myAssetContainer, "Data/Resource/Texture/T_tree.dds", { 32.f, 32.f });

			ResourceComponent* resource = entity->AddComponent<ResourceComponent>();
			resource->Init(TREE);

			CU::Vector2<float> pos;
			pos.x = 128.f + x * (32.f + 1.f);
			pos.y = 128.f + y * (32.f + 1.f);

			entity->SetPosition(pos);

			myEntities.Add(entity);
		}
	}

	for (int x = 1; x < 3; ++x)
	{
		for (int y = 1; y < 3; ++y)
		{
			Entity* entity = new Entity();

			SpriteComponent* sprite = entity->AddComponent<SpriteComponent>();
			sprite->Init(aEngine.GetAssetContainer(), "Data/Resource/Texture/T_water.dds", { 32.f, 32.f });

			ResourceComponent* resource = entity->AddComponent<ResourceComponent>();
			resource->Init(WATER);

			CU::Vector2<float> pos;
			pos.x = 128.f + x * (32.f + 1.f);
			pos.y = 128.f + y * (32.f + 1.f);

			entity->SetPosition(pos);

			myEntities.Add(entity);
		}
	}

	for (int x = 1; x < 3; ++x)
	{
		for (int y = 7; y < 9; ++y)
		{
			Entity* entity = new Entity();

			SpriteComponent* sprite = entity->AddComponent<SpriteComponent>();
			sprite->Init(*myAssetContainer, "Data/Resource/Texture/T_stock_pile.dds", { 32.f, 32.f });

			StockpileComponent* stockpile = entity->AddComponent<StockpileComponent>();
			stockpile->Init(*myAssetContainer);

			CU::Vector2<float> pos;
			pos.x = 128.f + x * (32.f + 1.f);
			pos.y = 128.f + y * (32.f + 1.f);

			entity->SetPosition(pos);

			myEntities.Add(entity);
		}
	}

	CreateWorker();
	mySpawnTimer = 10.f;
}

bool Game::Update(float aDelta)
{
	CU::InputWrapper* input = CU::InputWrapper::GetInstance();

	if (input->KeyIsPressed(DIK_ESCAPE))
	{
		return false;
	}

	for each (Entity* entity in myEntities)
	{
		entity->Update(aDelta);
		entity->Render(*myRendererProxy);
	}

	mySpawnTimer -= aDelta;
	if (mySpawnTimer <= 0.f)
	{
		mySpawnTimer = 10.f;
		CreateWorker();
	}

	return true;
}

void Game::OnResize(float aWidth, float aHeight)
{
	//throw std::logic_error("The method or operation is not implemented.");
}

void Game::CreateWorker()
{
	Entity* entity = new Entity();

	SpriteComponent* sprite = entity->AddComponent<SpriteComponent>();
	sprite->Init(*myAssetContainer, "Data/Resource/Texture/T_unit.dds", { 32.f, 32.f });

	GOAPComponent* goap = entity->AddComponent<GOAPComponent>();
	goap->Init();

	myEntities.Add(entity);
}
