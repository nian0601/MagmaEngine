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
	}

	void Profiler::Render(RendererProxy& aRendererProxy)
	{
		CU::Vector2<float> drawPos;
		drawPos.x = 512.f;
		drawPos.y = myFont->GetMaxHeight();
		
		for (const ProfilerEntry* entry : myEntries)
		{
			RenderEntry(aRendererProxy, entry, drawPos);
		}

		myEntries.DeleteAll();
		myCurrentEntry = nullptr;
	}

	void Profiler::StartEntry(const char* aText)
	{
		if (!myCurrentEntry)
		{
			myEntries.Add(new ProfilerEntry());
			myCurrentEntry = myEntries.GetLast();
		}
		else
		{
			myCurrentEntry->myChildren.Add(new ProfilerEntry());
			ProfilerEntry* temp = myCurrentEntry;
			myCurrentEntry = myCurrentEntry->myChildren.GetLast();
			myCurrentEntry->myParent = temp;
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

		myCurrentEntry->myDuration = static_cast<float>(currTime - myCurrentEntry->myStartTime) / 1000000.f;

		if (myCurrentEntry->myParent)
			myCurrentEntry = myCurrentEntry->myParent;
		else
			myCurrentEntry = nullptr;
	}

	void Profiler::RenderEntry(RendererProxy& aRendererProxy, const ProfilerEntry* aEntry, CU::Vector2<float>& aDrawPos)
	{
		CU::String output(aEntry->myText);
		output += ": ";
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