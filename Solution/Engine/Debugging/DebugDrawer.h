#pragma once

#include <CUString.h>


#define DEBUG_TEXT_X 10.f
#define DEBUG_TEXT_Y 10.f
#define DEBUG_TEXT_SPACING 10.f

namespace Magma
{
	struct DebugText
	{
		DebugText(){}
		DebugText(const CU::String& aString, float aY)
			: myString(aString)
			, myY(aY)
		{}

		CU::String myString;
		float myY;
	};

	class DebugDrawer
	{
	public:
		static DebugDrawer* GetInstance();
		static void Destroy();

		void AddDebugText(const CU::String& aString);
		const CU::GrowingArray<DebugText>& GetDebugTexts() const { return myDebugTexts; }
		void ClearDebugTexts() { myDebugTexts.RemoveAll(); }

	private:
		DebugDrawer();
		~DebugDrawer();


		CU::GrowingArray<DebugText> myDebugTexts;

		static DebugDrawer* ourInstance;
	};
}