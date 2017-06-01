#include "stdafx.h"
#include "NavGrid.h"


NavGrid::NavGrid()
{
}


NavGrid::~NavGrid()
{
}

void NavGrid::Init(int aGridSize)
{
	myMoveCost = 100;

	myGridSize = aGridSize;
	myGrid.Reserve(myGridSize * myGridSize);

	for (int i = 0; i < myGridSize * myGridSize; ++i)
		myGrid[i].myGridIndex = i;

	ResetGrid();
}

bool NavGrid::FindPath(const CU::Vector3f& aStartPoint, const CU::Vector3f& aEndPoint, CU::GrowingArray<CU::Vector2f>& aOutPath)
{
	CU::Vector2i startPos(static_cast<int>(aStartPoint.x), static_cast<int>(aStartPoint.z));
	CU::Vector2i endPos(static_cast<int>(aEndPoint.x), static_cast<int>(aEndPoint.z));

	return FindPath(startPos, endPos, aOutPath);
}

bool NavGrid::FindPath(const CU::Vector2i& aStartPoint, const CU::Vector2i& aEndPoint, CU::GrowingArray<CU::Vector2f>& aOutPath)
{
	aOutPath.RemoveAll();
	ResetGrid();

	int startIndex = WorldIndexToGridIndex(aStartPoint);
	int goalIndex = WorldIndexToGridIndex(aEndPoint);

	if (!IsPositionOnGrid(aStartPoint) || !IsPositionOnGrid(aEndPoint))
		return false;

	Node& startNode = myGrid[startIndex];
	startNode.myG = 0;
	startNode.myH = CalculateHeuristic(startIndex, goalIndex);
	startNode.myF = startNode.myG + startNode.myH;
	startNode.myListState = IN_OPEN;

	Node* currentClosestNode = &myGrid[startIndex];

	CU::Heap<Node*, NavGrid_NodeComparer<Node*>> heap;
	heap.Enqueue(&startNode);

	while (!heap.IsEmpty())
	{
		Node* currNode = heap.Dequeue();
		currNode->myListState = IN_CLOSED;

		if (CalculateHeuristic(currNode->myGridIndex, goalIndex) < currentClosestNode->myH)
			currentClosestNode = currNode;

		if (currNode->myGridIndex == goalIndex)
		{
			while (currNode != nullptr)
			{
				CU::Vector2f worldPosition = ArrayIndexToWorldPosition(currNode->myGridIndex);
				aOutPath.Add(worldPosition);
				currNode = currNode->myParent;
			}

			return true;
		}

		int currIndex = currNode->myGridIndex;

		if (currIndex > myGridSize)
		{
			ExamineNeighbour(currNode, currIndex - myGridSize, goalIndex, heap);
		}

		if (currIndex < myGridSize * (myGridSize - 1))
		{
			ExamineNeighbour(currNode, currIndex + myGridSize, goalIndex, heap);
		}

		if (currIndex % myGridSize != 0)
		{
			ExamineNeighbour(currNode, currIndex - 1, goalIndex, heap);
		}

		if ((currIndex + 1) % myGridSize != 0)
		{
			ExamineNeighbour(currNode, currIndex + 1, goalIndex, heap);
		}

		currNode->myListState = IN_CLOSED;
	}

	return FindPath(aStartPoint, ArrayIndexToGridIndex(currentClosestNode->myGridIndex), aOutPath);
}

void NavGrid::BlockCell(const CU::Vector3f& aWorldPos)
{
	CU::Vector2i gridIndex(static_cast<int>(aWorldPos.x), static_cast<int>(aWorldPos.z));
	BlockCell(gridIndex);
}

void NavGrid::BlockCell(const CU::Vector2i& aCellIndex)
{
	if (!IsPositionOnGrid(aCellIndex))
		return;

	int gridIndex = WorldIndexToGridIndex(aCellIndex);
	myGrid[gridIndex].myIsWalkable = false;
}

void NavGrid::UnBlockCell(const CU::Vector3f& aWorldPos)
{
	CU::Vector2i gridIndex(static_cast<int>(aWorldPos.x), static_cast<int>(aWorldPos.z));
	UnBlockCell(gridIndex);
}

void NavGrid::UnBlockCell(const CU::Vector2i& aCellIndex)
{
	if (!IsPositionOnGrid(aCellIndex))
		return;

	int gridIndex = WorldIndexToGridIndex(aCellIndex);
	myGrid[gridIndex].myIsWalkable = true;
}

void NavGrid::ExamineNeighbour(Node* aCurrentNode, int aNeighbourIndex, int aGoalIndex, CU::Heap<Node*, NavGrid_NodeComparer<Node*>>& aHeap)
{
	if (aNeighbourIndex < 0 || aNeighbourIndex > myGrid.Size() - 1) return;

	Node* neighbour = &myGrid[aNeighbourIndex];

	if (neighbour->myListState == IN_CLOSED || !neighbour->myIsWalkable)
		return;

	if (neighbour->myListState == IN_OPEN)
	{
		if (neighbour->myG > aCurrentNode->myG + myMoveCost)
		{
			UpdateNodeValues(aCurrentNode, neighbour, aGoalIndex);
			aHeap.Heapify();
		}
	}
	else
	{
		neighbour->myListState = IN_OPEN;
		UpdateNodeValues(aCurrentNode, neighbour, aGoalIndex);
		aHeap.Enqueue(neighbour);
	}
}

void NavGrid::UpdateNodeValues(Node* aParent, Node* aNodeToUpdate, int aGoalIndex)
{
	aNodeToUpdate->myH = CalculateHeuristic(aNodeToUpdate->myGridIndex, aGoalIndex);
	aNodeToUpdate->myG = aParent->myG + myMoveCost;
	aNodeToUpdate->myF = aNodeToUpdate->myG + aNodeToUpdate->myH;
	aNodeToUpdate->myParent = aParent;
}

void NavGrid::ResetGrid()
{
	for (int i = 0; i < myGridSize * myGridSize; ++i)
		myGrid[i].Reset();
}

int NavGrid::CalculateHeuristic(int aFirstIndex, int aSecondIndex) const
{
	CU::Vector2i firstGridIndex = ArrayIndexToGridIndex(aFirstIndex);
	CU::Vector2i secondGridIndex = ArrayIndexToGridIndex(aSecondIndex);

	return abs(firstGridIndex.x - secondGridIndex.x) + abs(firstGridIndex.y - secondGridIndex.y);
}

int NavGrid::WorldIndexToGridIndex(const CU::Vector2i& aIndex) const
{
	return aIndex.y * myGridSize + aIndex.x;
}

CU::Vector2i NavGrid::ArrayIndexToGridIndex(const int aIndex) const
{
	return CU::Vector2<int>(aIndex % myGridSize, aIndex / myGridSize);
}

CU::Vector2f NavGrid::ArrayIndexToWorldPosition(const int aIndex) const
{
	CU::Vector2i gridIndex = ArrayIndexToGridIndex(aIndex);

	CU::Vector2f worldPosition;
	worldPosition.x = static_cast<float>(gridIndex.x);
	worldPosition.y = static_cast<float>(gridIndex.y);

	return worldPosition;
}

bool NavGrid::IsPositionOnGrid(const CU::Vector2i& anIndex) const
{
	if (anIndex.x < 0 || anIndex.y < 0 || anIndex.x >= myGridSize || anIndex.y >= myGridSize)
	{
		return false;
	}

	return true;
}