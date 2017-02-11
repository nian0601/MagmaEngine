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

	void Profiler::AddEntry(const CU::String& aText, float aDuration)
	{
		myEntries.Add({ aText, aDuration });
	}

	void Profiler::Render(RendererProxy& aRendererProxy)
	{
		float y = myFont->GetMaxHeight();
		for (const ProfilerEntry& entry : myEntries)
		{
			CU::String output(entry.myText);
			output += ": ";
			output += entry.myDuration;

			aRendererProxy.RenderText(myFont, output, { 512.f, y });

			y += myFont->GetMaxHeight();
		}

		myEntries.RemoveAll();
	}

	Profiler::Profiler()
		: myFont(nullptr)
	{
	}


	Profiler::~Profiler()
	{
	}
}