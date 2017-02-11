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

		void Render(RendererProxy& aRendererProxy);

		void StartEntry(const char* aText);
		void EndEntry();

	private:
		struct ProfilerEntry
		{
			/*ProfilerEntry(const CU::String& aString, float aDuration)
				: myText(aString)
				, myDuration(aDuration)
				, myParent(nullptr)
			{
				myChildren.Init(16);
			}*/
			ProfilerEntry()
				: myParent(nullptr)
			{
			}
			~ProfilerEntry()
			{
				myParent = nullptr;
				myChildren.DeleteAll();
			}
			CU::String myText;
			float myDuration;
			unsigned long long myStartTime;

			ProfilerEntry* myParent;
			CU::GrowingArray<ProfilerEntry*> myChildren;
		};

		void RenderEntry(RendererProxy& aRendererProxy, const ProfilerEntry* aEntry, CU::Vector2<float>& aDrawPos);

		CU::GrowingArray<ProfilerEntry*> myEntries;
		ProfilerEntry* myCurrentEntry;
		Font* myFont;

		unsigned long long myFrequency;

		Profiler();
		~Profiler();
		static Profiler* ourInstance;
	};
}