#pragma once

#define PROFILE_FUNCTION Magma::ProfilerInclude __profilerInclude__(__FUNCTION__)

namespace Magma
{
	class ProfilerInclude
	{
	public:
		ProfilerInclude(const char* aString);
		~ProfilerInclude();

	private:
		unsigned long long myStartTime;
		unsigned long long myFrequency;
		const char* myString;
	};
}
