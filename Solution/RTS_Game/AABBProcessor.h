#pragma once

#include <Entity/Include/BaseProcessor.h>

namespace Magma
{
	class Camera;
}

class AABBProcessor : public Magma::BaseProcessor
{
public:
	AABBProcessor(Magma::World& aWorld, const Magma::Camera& aCamera);
	~AABBProcessor();

	void Update(float aDelta) override;

private:

	CU::Vector3<float> Unproject(float aX, float aY, float aZ);

	const Magma::Camera& myCamera;
};

