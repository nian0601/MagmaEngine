#pragma once

#include <StaticArray.h>
#include <Entity/Include/TypeID.h>
#include <Matrix.h>

namespace Magma
{
	class RendererProxy;
}

class IComponent;
class Entity
{
public:
	Entity();
	~Entity();

	void Update(float aDelta);
	void Render(Magma::RendererProxy& aRendererProxy);

	template <typename T>
	T* AddComponent();

	template <typename T>
	T* GetComponent();

	template <typename T>
	void DeleteComponent();

	CU::Vector2<float> GetPosition() const;
	void SetPosition(const CU::Vector2<float>& aPosition);

private:
	CU::Matrix33<float> myOrientation;

	static const int myMaxNumComponents = 8;
	CU::StaticArray<IComponent*, myMaxNumComponents> myComponents;
};

template <typename T>
T* Entity::AddComponent()
{
	int componentID = Magma::TypeID<IComponent>::GetID<T>();
	DL_ASSERT_EXP(componentID < myMaxNumComponents, "myMaxNumComponents is to low, found component with higher ID");
	DL_ASSERT_EXP(myComponents[componentID] == nullptr, "Tried to add duplicate component");

	T* newComp = new T(*this);
	myComponents[componentID] = newComp;
	return newComp;
}

template <typename T>
T* Entity::GetComponent()
{
	int componentID = Magma::TypeID<IComponent>::GetID<T>();
	DL_ASSERT_EXP(componentID < myMaxNumComponents, "myMaxNumComponents is to low, found component with higher ID");

	return static_cast<T*>(myComponents[componentID]);
}

template <typename T>
void Entity::DeleteComponent()
{
	int componentID = Magma::TypeID<IComponent>::GetID<T>();
	DL_ASSERT_EXP(componentID < myMaxNumComponents, "myMaxNumComponents is to low, found component with higher ID");
	DL_ASSERT_EXP(myComponents[componentID] != nullptr, "Tried to delete nonexisting component");

	delete myComponents[componentID];
	myComponents[componentID] = nullptr;
}
