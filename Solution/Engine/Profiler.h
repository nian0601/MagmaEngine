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
		void EndFrame();

		void Render(RendererProxy& aRendererProxy);

		void StartEntry(const char* aText);
		void EndEntry();

	private:
		struct ProfilerEntry
		{
			ProfilerEntry()
				: myParent(nullptr)
				, myDuration(0.f)
				, myCount(0)
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
			int myCount;

			ProfilerEntry* myParent;
			CU::GrowingArray<ProfilerEntry*> myChildren;
		};

		void RenderEntry(RendererProxy& aRendererProxy, const ProfilerEntry* aEntry, CU::Vector2<float>& aDrawPos);

		typedef CU::GrowingArray<ProfilerEntry*> EntryArray;
		//CU::GrowingArray<ProfilerEntry*> myEntries;
		EntryArray myEntries[2];
		//CU::StaticArray<EntryArray, 2> myEntries;
		int myActiveArrayIndex;
		ProfilerEntry* myCurrentEntry;
		Font* myFont;

		unsigned long long myFrequency;

		Profiler();
		~Profiler();
		static Profiler* ourInstance;
	};
}