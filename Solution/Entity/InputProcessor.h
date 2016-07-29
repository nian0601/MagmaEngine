#pragma once
#include "BaseProcessor.h"
class InputProcessor :
	public BaseProcessor
{
public:
	InputProcessor(World& aWorld);
	~InputProcessor();

	void Update(float aDelta) override;
};

