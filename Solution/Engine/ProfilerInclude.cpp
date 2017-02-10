#include "stdafx.h"
#include "ProfilerInclude.h"
#include <TimerManager.h>
#include "Profiler.h"

namespace Magma
{
	ProfilerInclude::ProfilerInclude(const char* aString)
		: myString(aString)
	{
		LARGE_INTEGER largeInteger;
		QueryPerformanceFrequency(&largeInteger);
		myFrequency = largeInteger.QuadPart;

		QueryPerformanceCounter(&largeInteger);
		myStartTime = largeInteger.QuadPart * 1000000 / myFrequency;
	}


	ProfilerInclude::~ProfilerInclude()
	{
		LARGE_INTEGER largeInteger;
		QueryPerformanceCounter(&largeInteger);
		unsigned long long currTime = largeInteger.QuadPart * 1000000 / myFrequency;

		float duration = static_cast<float>(currTime - myStartTime) / 1000000.f;

		Profiler::GetInstance()->AddEntry(myString, duration);
	}
}