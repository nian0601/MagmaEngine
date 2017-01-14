#pragma once

#include "IComponent.h"
#include "EntityDefines.h"

namespace Magma
{
	class AssetContainer;
	class Texture;
}

class ResourceComponent : public IComponent
{
public:
	ResourceComponent(Entity& anEntity);
	~ResourceComponent();

	virtual void Init(eResourceType aResourceType, Magma::AssetContainer& anAssetContainer);

	eResourceType GetResourceType() const { return myResourceType; }
	Magma::Texture* GetStockpileTexture() const { return myStockpileTexture; }

private:
	eResourceType myResourceType;
	Magma::Texture* myStockpileTexture;
};

