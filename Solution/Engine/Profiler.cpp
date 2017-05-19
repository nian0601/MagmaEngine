#include "stdafx.h"

#include "AssetContainer.h"
#include "Font.h"
#include "Profiler.h"
#include "RendererProxy.h"

namespace Magma
{
	Profiler* Profiler::ourInstance = nullptr;

	Profiler* Profiler::GetInstance()
	{
		if (!ourInstance)
			ourInstance = new Profiler();

		return ourInstance;
	}

	void Profiler::Destroy()
	{
		SAFE_DELETE(ourInstance);
	}

	
	void Profiler::Init(AssetContainer& aAssetContainer)
	{
		myFont = aAssetContainer.LoadFont("Data/Resource/Font/Font.png");
		myActiveArrayIndex = 0;
	}

	void Profiler::EndFrame()
	{
		myEntries[myActiveArrayIndex].DeleteAll();
		myActiveArrayIndex ^= 1;
		myCurrentEntry = nullptr;
	}

	void Profiler::Render(RendererProxy& aRendererProxy)
	{
		PROFILE_FUNCTION;
		CU::Vector2<float> drawPos;
		drawPos.x = 512.f;
		drawPos.y = myFont->GetMaxHeight();
		
		EntryArray& entries = myEntries[myActiveArrayIndex];
		for (const ProfilerEntry* entry : entries)
		{
			PROFILE_START("Render Entry");
			RenderEntry(aRendererProxy, entry, drawPos);
			PROFILE_END();
		}
	}

	void Profiler::StartEntry(const char* aText)
	{
		EntryArray& entries = myEntries[myActiveArrayIndex ^ 1];
		if (!myCurrentEntry)
		{
			entries.Add(new ProfilerEntry());
			myCurrentEntry = entries.GetLast();
		}
		else
		{
			ProfilerEntry* existingEntry = nullptr;
			for (ProfilerEntry* entry : myCurrentEntry->myChildren)
			{
				if (entry->myText == aText)
				{
					existingEntry = entry;
					break;
				}
			}

			if (!existingEntry)
			{
				myCurrentEntry->myChildren.Add(new ProfilerEntry());
				ProfilerEntry* temp = myCurrentEntry;
				myCurrentEntry = myCurrentEntry->myChildren.GetLast();
				myCurrentEntry->myParent = temp;
			}
			else
			{
				myCurrentEntry = existingEntry;
			}
		}

		LARGE_INTEGER largeInteger;
		QueryPerformanceCounter(&largeInteger);
		myCurrentEntry->myStartTime = largeInteger.QuadPart * 1000000 / myFrequency;
		myCurrentEntry->myText = aText;
	}

	void Profiler::EndEntry()
	{
		DL_ASSERT_EXP(myCurrentEntry != nullptr, "Missing a current entry, fucked up with Start/End-entry");

		LARGE_INTEGER largeInteger;
		QueryPerformanceCounter(&largeInteger);
		unsigned long long currTime = largeInteger.QuadPart * 1000000 / myFrequency;

		myCurrentEntry->myDuration += static_cast<float>(currTime - myCurrentEntry->myStartTime) / 1000000.f;
		++myCurrentEntry->myCount;

		if (myCurrentEntry->myParent)
			myCurrentEntry = myCurrentEntry->myParent;
		else
			myCurrentEntry = nullptr;
	}

	void Profiler::RenderEntry(RendererProxy& aRendererProxy, const ProfilerEntry* aEntry, CU::Vector2<float>& aDrawPos)
	{
		CU::String output(aEntry->myText);
		output += " (";
		output += aEntry->myCount;
		output += "): ";
		output += aEntry->myDuration;

		aRendererProxy.RenderText(myFont, output, { aDrawPos.x, aDrawPos.y });
		aDrawPos.y += myFont->GetMaxHeight();

		aDrawPos.x += 20.f;
		for (const ProfilerEntry* entry : aEntry->myChildren)
		{
			RenderEntry(aRendererProxy, entry, aDrawPos);
		}
		aDrawPos.x -= 20.f;
	}

	Profiler::Profiler()
		: myFont(nullptr)
		, myCurrentEntry(nullptr)
	{
		LARGE_INTEGER largeInteger;
		QueryPerformanceFrequency(&largeInteger);
		myFrequency = largeInteger.QuadPart;
	}


	Profiler::~Profiler()
	{
	}
}