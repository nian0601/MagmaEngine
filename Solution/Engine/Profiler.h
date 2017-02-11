#pragma once

namespace Magma
{
	class AssetContainer;
	class Font;
	class RendererProxy;
	class Profiler
	{
	public:

		static Profiler* GetInstance();
		static void Destroy();

		void Init(AssetContainer& aAssetContainer);

		void AddEntry(const CU::String& aText, float aDuration);

		void Render(RendererProxy& aRendererProxy);

	private:
		struct ProfilerEntry
		{
			ProfilerEntry(const CU::String& aString, float aDuration)
				: myText(aString)
				, myDuration(aDuration)
			{}
			ProfilerEntry(){}
			CU::String myText;
			float myDuration;
		};

		CU::GrowingArray<ProfilerEntry> myEntries;
		Font* myFont;

		Profiler();
		~Profiler();
		static Profiler* ourInstance;
	};
}