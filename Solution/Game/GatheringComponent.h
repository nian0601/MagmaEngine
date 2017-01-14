#pragma once

#include "IComponent.h"
#include "EntityDefines.h"

class GatheringComponent : public IComponent
{
public:
	GatheringComponent(Entity& anEntity);
	~GatheringComponent();

	void SetResourceType(eResourceType aResourceType) { myResourceType = aResourceType; };
	eResourceType GetResourceType() const { return myResourceType; }

private:
	eResourceType myResourceType;
};

