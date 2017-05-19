#include "stdafx.h"

#include <AssetContainer.h>
#include <Camera.h>
#include <Engine.h>
#include "Game.h"
#include <RendererProxy.h>


#include "Entity.h"
#include "SpriteComponent.h"
#include "ResourceComponent.h"
#include "GOAPComponent.h"
#include "StockpileComponent.h"

#include "PollingStation.h"

#include "EntityFactory.h"

#include <DebugDrawer.h>

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
	EntityFactory::Create(aEngine);

	myCamera = &aEngine.GetCamera();
	myCamera->Move({ 0.f, 0.f, -30.f });

	myRendererProxy = &aEngine.GetRendererProxy();
	myAssetContainer = &aEngine.GetAssetContainer();

	myEntities.Init(128);

	for (int x = 0; x < 10; ++x)
	{
		for (int y = 0; y < 10; ++y)
		{
			myEntities.Add(EntityFactory::CreateGroundEntity(x, y));
		}
	}

	for (int x = 6; x < 9; ++x)
	{
		for (int y = 6; y < 9; ++y)
		{
			myEntities.Add(EntityFactory::CreateTreeEntity(x, y));
		}
	}

	for (int x = 1; x < 3; ++x)
	{
		for (int y = 1; y < 3; ++y)
		{
			myEntities.Add(EntityFactory::CreateWaterEntity(x, y));
		}
	}

	for (int x = 1; x < 3; ++x)
	{
		for (int y = 7; y < 9; ++y)
		{
			myEntities.Add(EntityFactory::CreateStockpileEntity(x, y));
		}
	}

	CreateWorker();
	CreateWorker();
	CreateWorker();
	CreateWorker();
	myAssignWorkTimer = 5.f;
	myTargetTreeCount = 3;
	myTargetWaterCount = 5;
}

bool Game::Update(float aDelta)
{
	PROFILE_FUNCTION;

	CU::InputWrapper* input = CU::InputWrapper::GetInstance();

	if (input->KeyIsPressed(DIK_ESCAPE))
	{
		return false;
	}

	PROFILE_START("Entity Update");
	for each (Entity* entity in myEntities)
	{
		entity->Update(aDelta);
		entity->Render(*myRendererProxy);
	}
	PROFILE_END();

	myAssignWorkTimer -= aDelta;
	if (myAssignWorkTimer <= 0.f)
	{
		myAssignWorkTimer = 5.f;

		int treeCount = PollingStation::GetInstance()->GetResourceCount(eResourceType::TREE);
		int waterCount = PollingStation::GetInstance()->GetResourceCount(eResourceType::WATER);

		GOAPGameState goalState;

		
		if (myIdleWorkers.Size() > 0)
		{
			if (treeCount < myTargetTreeCount)
				goalState.SetWorldState(eWorldState::HAS_WOOD_ON_STOCKPILE, true);
			else if (waterCount < myTargetWaterCount)
				goalState.SetWorldState(eWorldState::HAS_WATER_ON_STOCKPILE, true);

			ActivateWorker(myIdleWorkers[0], goalState);
		}
	}

	UpdateWorkerStatus();

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

	GOAPGameState entityStartState;
	entityStartState.SetEntityState(eEntityState::CAN_GATHER_WATER, true);
	entityStartState.SetEntityState(eEntityState::CAN_GATHER_WOOD, true);
	entity->ModifyGOAPState(entityStartState);

	myEntities.Add(entity);
	myIdleWorkers.Add(entity);
}

void Game::UpdateWorkerStatus()
{
	for (int i = myActiveWorkers.Size()-1; i >= 0; --i)
	{
		Entity* worker = myActiveWorkers[i];
		GOAPComponent* goapComp = worker->GetComponent<GOAPComponent>();
		if (!goapComp->HasActivePlan())
		{
			myIdleWorkers.Add(worker);
			myActiveWorkers.RemoveCyclicAtIndex(i);
		}
	}
}

void Game::ActivateWorker(Entity* aWorker, const GOAPGameState& aGoalState)
{
	myIdleWorkers.RemoveCyclic(aWorker);
	myActiveWorkers.Add(aWorker);

	GOAPComponent* goapComp = aWorker->GetComponent<GOAPComponent>();

	goapComp->StartPlan(aGoalState);
}
