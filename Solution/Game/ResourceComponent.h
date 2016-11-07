#pragma once

#include "IComponent.h"
#include "EntityDefines.h"

class ResourceComponent : public IComponent
{
public:
	ResourceComponent(Entity& anEntity);
	~ResourceComponent();

	virtual void Init(eResourceType aResourceType);
	virtual void Update(float) override;

	eResourceType GetResourceType() const { return myResourceType; }

private:
	eResourceType myResourceType;
};

