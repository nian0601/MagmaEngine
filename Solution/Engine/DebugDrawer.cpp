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
		myDebugTexts.Add({ aString, GetNextY() });
	}

	void DebugDrawer::AddDebugText(const CU::String& aString, float aValue)
	{
		CU::String string(aString);
		string += ": ";
		string += aValue;
		myDebugTexts.Add({ string, GetNextY() });
	}

	void DebugDrawer::AddDebugText(const CU::String& aString, int aValue)
	{
		CU::String string(aString);
		string += ": ";
		string += aValue;
		myDebugTexts.Add({ string, GetNextY() });
	}

	void DebugDrawer::AddDebugText(const CU::String& aString, const CU::String& aValue)
	{
		CU::String string(aString);
		string += ": ";
		string += aValue;
		myDebugTexts.Add({ string, GetNextY() });
	}

	void DebugDrawer::AddDebugText(const CU::String& aString, const CU::Vector2<float>& aValue)
	{
		CU::String string(aString);
		string += ": X: ";
		string += aValue.x;
		string += ", Y: ";
		string += aValue.y;
		myDebugTexts.Add({ string, GetNextY() });
	}

	void DebugDrawer::AddDebugText(const CU::String& aString, const CU::Vector3<float>& aValue)
	{
		CU::String string(aString);
		string += ": X: ";
		string += aValue.x;
		string += ", Y: ";
		string += aValue.y;
		string += ", Z: ";
		string += aValue.z;
		myDebugTexts.Add({ string, GetNextY() });
	}

	void DebugDrawer::AddDebugText(const CU::String& aString, const CU::Vector4<float>& aValue)
	{
		CU::String string(aString);
		string += ": X: ";
		string += aValue.x;
		string += ", Y: ";
		string += aValue.y;
		string += ", Z: ";
		string += aValue.z;
		string += ", W: ";
		string += aValue.w;
		myDebugTexts.Add({ string, GetNextY() });
	}

	void DebugDrawer::AddDebugText(const CU::String& aString, const CU::Vector2<int>& aValue)
	{
		CU::String string(aString);
		string += ": X: ";
		string += aValue.x;
		string += ", Y: ";
		string += aValue.y;
		myDebugTexts.Add({ string, GetNextY() });
	}

	void DebugDrawer::AddDebugText(const CU::String& aString, const CU::Vector3<int>& aValue)
	{
		CU::String string(aString);
		string += ": X: ";
		string += aValue.x;
		string += ", Y: ";
		string += aValue.y;
		string += ", Z: ";
		string += aValue.z;
		myDebugTexts.Add({ string, GetNextY() });
	}

	void DebugDrawer::AddDebugText(const CU::String& aString, const CU::Vector4<int>& aValue)
	{
		CU::String string(aString);
		string += ": X: ";
		string += aValue.x;
		string += ", Y: ";
		string += aValue.y;
		string += ", Z: ";
		string += aValue.z;
		string += ", W: ";
		string += aValue.w;
		myDebugTexts.Add({ string, GetNextY() });
	}

	DebugDrawer::DebugDrawer()
	{
	}


	DebugDrawer::~DebugDrawer()
	{
	}

	float DebugDrawer::GetNextY() const
	{
		float y = DEBUG_TEXT_Y;
		if (myDebugTexts.Size() > 0)
			y = myDebugTexts.GetLast().myY;

		y += DEBUG_TEXT_SPACING;
		return y;
	}

}