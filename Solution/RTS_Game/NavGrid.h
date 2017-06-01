#pragma once

#include <GrowingArray.h>

#include <Heap.h>

template<typename T>
class NavGrid_NodeComparer
{
public:
	bool operator()(T a, T b)
	{
		return a->myF < b->myF;
	}
};

class NavGrid
{
public:
	NavGrid();
	~NavGrid();

	void Init(int aGridSize);

	bool FindPath(const CU::Vector3f& aStartPoint, const CU::Vector3f& aEndPoint, CU::GrowingArray<CU::Vector2f>& aOutPath);
	bool FindPath(const CU::Vector2i& aStartPoint, const CU::Vector2i& aEndPoint, CU::GrowingArray<CU::Vector2f>& aOutPath);

	void BlockCell(const CU::Vector3f& aWorldPos);
	void BlockCell(const CU::Vector2i& aCellIndex);
	void UnBlockCell(const CU::Vector3f& aWorldPos);
	void UnBlockCell(const CU::Vector2i& aCellIndex);

private:
	enum eListState
	{
		NOT_VISITED,
		IN_OPEN,
		IN_CLOSED,
	};

	struct Node
	{
		Node()
			: myIsWalkable(true)
			, myGridIndex(-1)
		{
			Reset();
		}

		void Reset()
		{
			myListState = NOT_VISITED;
			myH = 0;
			myG = 0;
			myF = 0;
			myParent = nullptr;
		}

		eListState myListState;
		int myH;
		int myG;
		int myF;
		Node* myParent;
		bool myIsWalkable;
		int myGridIndex;
	};

	void ExamineNeighbour(Node* aCurrentNode, int aNeighbourIndex, int aGoalIndex, CU::Heap<Node*, NavGrid_NodeComparer<Node*>>& aHeap);
	void UpdateNodeValues(Node* aParent, Node* aNodeToUpdate, int aGoalIndex);
	void ResetGrid();

	int CalculateHeuristic(int aFirstIndex, int aSecondIndex) const;

	int WorldIndexToGridIndex(const CU::Vector2i& aIndex) const;
	CU::Vector2i ArrayIndexToGridIndex(const int aIndex) const;
	CU::Vector2f ArrayIndexToWorldPosition(const int aIndex) const;
	bool IsPositionOnGrid(const CU::Vector2i& anIndex) const;
	

	int myGridSize;
	CU::GrowingArray<Node> myGrid;
	int myMoveCost;
};

