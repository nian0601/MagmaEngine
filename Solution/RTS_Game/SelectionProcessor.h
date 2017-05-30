#pragma once

#include <Entity/Include/BaseProcessor.h>

namespace Magma
{
	class Camera;
}

class SelectionProcessor : public Magma::BaseProcessor
{
public:
	SelectionProcessor(Magma::World& aWorld, const Magma::Camera& aCamera);
	~SelectionProcessor();

	void Update(float aDelta) override;

private:

	Magma::Entity FindEntityUnderCursor();
	CU::Vector3<float> Unproject(float aX, float aY, float aZ) const;

	const Magma::Camera& myCamera;
	CU::GrowingArray<Magma::Entity> mySelectedEntities;
};

