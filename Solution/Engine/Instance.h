#pragma once
#include "EngineTypes.h"
#include <Matrix.h>

namespace Easy3D
{
	class Camera;
	class Renderer;

	class Instance
	{
	public:
		Instance(ModelID aModelID, EffectID aEffect);
		~Instance();

		void Render();
		void Render(Renderer* aRenderer, const Camera& aCamera);

		void SetPosition(const CU::Vector3<float>& aPosition);
		CU::Vector3<float> GetPosition() const;

		void SetRotation(const CU::Vector3<float>& aRotation);
		void SetScale(const CU::Vector3<float>& aScale);

	private:
		void operator=(Instance&) = delete;

		CU::Matrix44<float> myOrientation;
		CU::Vector3<float> myScale;
		ModelID myModelID;
		EffectID myEffect;
	};
}