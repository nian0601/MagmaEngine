#pragma once

#include "EntityDefines.h"
#include "IComponent.h"
#include <CUString.h>
#include <Matrix.h>
#include <StaticArray.h>
#include <Vector.h>

namespace Magma
{
	class AssetContainer;
	class Texture;
}

class StockpileComponent : public IComponent
{
public:
	StockpileComponent(Entity& anEntity);
	~StockpileComponent();

	virtual void Init(Magma::AssetContainer& anAssetContainer);
	virtual void Update(float) override;
	virtual void Render(Magma::RendererProxy& aRendererProxy) override;

	bool IsFull() const;
	bool HasResource(eResourceType aResourceType) const;
	void PlaceResource(eResourceType aResourceType);
	void RemoveResource(eResourceType aResourceType);

	int GetResourceCount(eResourceType aResourceType) const;

private:
	enum eSlotIndex
	{
		TOP_LEFT = 0,
		TOP_RIGHT,
		BOTTOM_LEFT,
		BOTTOM_RIGHT,
	};
	struct Slot
	{
		Magma::Texture* myTexture;
		CU::Vector2<float> myPositionOffset;
		eResourceType myType;
	};

	CU::StaticArray<Slot, 4> mySlots;
	CU::Matrix44<float> myRenderOrientation;
	CU::StaticArray<Magma::Texture*, eResourceType::_RESOURCE_COUNT> myResourceTextures;
};

