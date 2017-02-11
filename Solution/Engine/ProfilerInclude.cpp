#include "stdafx.h"
#include "ProfilerInclude.h"
#include <TimerManager.h>
#include "Profiler.h"

namespace Magma
{
	ProfilerInclude::ProfilerInclude(const char* aString)
	{
		Profiler::GetInstance()->StartEntry(aString);
	}


	ProfilerInclude::~ProfilerInclude()
	{
		Profiler::GetInstance()->EndEntry();
	}
}