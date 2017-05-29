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

		void UpdateInput();

		void Render(RendererProxy& aRendererProxy);

		void StartEntry(const char* aText);
		void EndEntry();

	private:
		struct ProfilerEntry;
		typedef CU::GrowingArray<ProfilerEntry*> EntryArray;

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
			bool myIsCollapsed;

			ProfilerEntry* myParent;
			EntryArray myChildren;
		};

		void RenderEntry(RendererProxy& aRendererProxy, const ProfilerEntry* aEntry, CU::Vector2<float>& aDrawPos);

		
		EntryArray myEntries[2];
		int myActiveArrayIndex;
		ProfilerEntry* myCurrentEntry;
		ProfilerEntry* mySelectedEntry;
		Font* myFont;

		unsigned long long myFrequency;

		Profiler();
		~Profiler();
		static Profiler* ourInstance;
	};
}