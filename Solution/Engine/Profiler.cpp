#include "stdafx.h"
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

	
	void Profiler::AddEntry(const CU::String& aText, float aDuration)
	{
		myEntries.Add({ aText, aDuration });
	}

	void Profiler::Render(RendererProxy& aRendererProxy)
	{
		if (myEntries.Size() > 0)
		{
			CU::String output(myEntries[0].myText);
			output += ": ";
			output += myEntries[0].myDuration;

			aRendererProxy.RenderText(output, { 512.f, 512.f });
		}

		myEntries.RemoveAll();
	}

	Profiler::Profiler()
	{
	}


	Profiler::~Profiler()
	{
	}
}