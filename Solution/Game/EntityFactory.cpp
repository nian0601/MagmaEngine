#include "stdafx.h"
#include "EntityFactory.h"


#include "Entity.h"
#include "SpriteComponent.h"
#include "ResourceComponent.h"
#include "StockpileComponent.h"

#include <Engine.h>
#include <AssetContainer.h>

Magma::AssetContainer* EntityFactory::myAssetContainer = nullptr;
CU::Vector2<float> EntityFactory::myWorldOffset;
float EntityFactory::myTileSize;

void EntityFactory::Create(Magma::Engine& anEngine)
{
	myAssetContainer = &anEngine.GetAssetContainer();
	myWorldOffset = { 128.f, 128.f };
	myTileSize = 32.f;
}

Entity* EntityFactory::CreateGroundEntity(int aXIndex, int aYIndex)
{
	Entity* entity = new Entity();

	SpriteComponent* sprite = entity->AddComponent<SpriteComponent>();
	sprite->Init(*myAssetContainer, "Data/Resource/Texture/T_ground.dds", { 32.f, 32.f });

	CU::Vector2<float> pos;
	pos.x = aXIndex * myTileSize;
	pos.y = aYIndex * myTileSize;

	pos += myWorldOffset;

	entity->SetPosition(pos);

	return entity;
}

Entity* EntityFactory::CreateWaterEntity(int aXIndex, int aYIndex)
{
	Entity* entity = new Entity();

	SpriteComponent* sprite = entity->AddComponent<SpriteComponent>();
	sprite->Init(*myAssetContainer, "Data/Resource/Texture/T_water.dds", { 32.f, 32.f });

	ResourceComponent* resource = entity->AddComponent<ResourceComponent>();
	resource->Init(WATER);

	CU::Vector2<float> pos;
	pos.x = aXIndex * myTileSize;
	pos.y = aYIndex * myTileSize;

	pos += myWorldOffset;

	entity->SetPosition(pos);

	return entity;
}

Entity* EntityFactory::CreateTreeEntity(int aXIndex, int aYIndex)
{
	Entity* entity = new Entity();

	SpriteComponent* sprite = entity->AddComponent<SpriteComponent>();
	sprite->Init(*myAssetContainer, "Data/Resource/Texture/T_tree.dds", { 32.f, 32.f });

	ResourceComponent* resource = entity->AddComponent<ResourceComponent>();
	resource->Init(TREE);

	CU::Vector2<float> pos;
	pos.x = aXIndex * myTileSize;
	pos.y = aYIndex * myTileSize;

	pos += myWorldOffset;

	entity->SetPosition(pos);

	return entity;
}

Entity* EntityFactory::CreateStockpileEntity(int aXIndex, int aYIndex)
{
	Entity* entity = new Entity();

	SpriteComponent* sprite = entity->AddComponent<SpriteComponent>();
	sprite->Init(*myAssetContainer, "Data/Resource/Texture/T_stock_pile.dds", { 32.f, 32.f });

	StockpileComponent* stockpile = entity->AddComponent<StockpileComponent>();
	stockpile->Init(*myAssetContainer);

	CU::Vector2<float> pos;
	pos.x = aXIndex * myTileSize;
	pos.y = aYIndex * myTileSize;

	pos += myWorldOffset;

	entity->SetPosition(pos);

	return entity;
}