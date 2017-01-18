#pragma once

#include <GrowingArray.h>
#include "GOAPGameState.h"

class GOAPPlan;
class GOAPAction;

class GOAPPlanner
{
public:
	GOAPPlanner();
	~GOAPPlanner();

	GOAPPlan* CreatePlan(const CU::GrowingArray<GOAPAction*>& someAvailableActions, const GOAPGameState& aWorldState, const GOAPGameState& aGoalState);

private:
	struct Node
	{
		Node(Node* aParent, GOAPGameState aState, GOAPAction* aAction)
			: myParent(aParent)
			, myState(aState)
			, myAction(aAction)
			, myChildren(8)
		{
			if (myParent)
				myParent->myChildren.Add(this);
		}

		~Node()
		{
			myChildren.DeleteAll();
		}

		GOAPGameState myState;
		GOAPAction* myAction;
		Node* myParent;

		//Only used to delete nodes after the Plan is finished
		CU::GrowingArray<Node*> myChildren;
	};

	bool BuildGraph(Node* aParent, const CU::GrowingArray<GOAPAction*>& someAvailableActions, const GOAPGameState& aGoalState, CU::GrowingArray<Node*>& someLeaves) const;
	bool IsInState(int aState, int aCondition) const;
	int GetNewState(int aCurrentState, int someNewEffects) const;
	Node* GetBestLeaf(const CU::GrowingArray<Node*>& someLeaves) const;
	CU::GrowingArray<GOAPAction*> GetActionsFromNode(const Node* aNode) const;
};

