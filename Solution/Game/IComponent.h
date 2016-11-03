#pragma once

namespace Magma
{
	class RendererProxy;
}

class Entity;
class IComponent
{
public:
	virtual ~IComponent() {}

	virtual void Update(float) {}
	virtual void Render(Magma::RendererProxy&) {}

protected:
	IComponent(Entity& anEntity)
	 : myEntity(anEntity)
	{}

	void operator=(const IComponent&) = delete;
	
	Entity& myEntity;
};

