#pragma once

namespace Magma
{
	class Engine;
	class AssetContainer;
}

class Entity;
class EntityFactory
{
public:

	static void Create(Magma::Engine& anEngine);

	static Entity* CreateGroundEntity(int aXIndex, int aYIndex);
	static Entity* CreateWaterEntity(int aXIndex, int aYIndex);
	static Entity* CreateTreeEntity(int aXIndex, int aYIndex);
	static Entity* CreateStockpileEntity(int aXIndex, int aYIndex);

private:
	EntityFactory() {};
	~EntityFactory() {};

	static Magma::AssetContainer* myAssetContainer;
	static CU::Vector2<float> myWorldOffset;
	static float myTileSize;
};

