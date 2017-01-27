#include "stdafx.h"
#include "DebugDrawer.h"


namespace Magma
{
	DebugDrawer* DebugDrawer::ourInstance = nullptr;

	DebugDrawer* DebugDrawer::GetInstance()
	{
		if (!ourInstance)
			ourInstance = new DebugDrawer();

		return ourInstance;
	}

	void DebugDrawer::Destroy()
	{
		SAFE_DELETE(ourInstance);
	}

	void DebugDrawer::AddDebugText(const CU::String& aString)
	{
		float y = DEBUG_TEXT_Y;
		if (myDebugTexts.Size() > 0)
			y = myDebugTexts.GetLast().myY;

		myDebugTexts.Add({ aString, y + DEBUG_TEXT_SPACING });
	}

	DebugDrawer::DebugDrawer()
	{
	}


	DebugDrawer::~DebugDrawer()
	{
	}
}