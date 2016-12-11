#pragma once

#include <GrowingArray.h>
#include "GOAPGameState.h"

class GOAPPlan;
class IGOAPAction;

class GOAPPlanner
{
public:
	GOAPPlanner();
	~GOAPPlanner();

	GOAPPlan* CreatePlan(const CU::GrowingArray<IGOAPAction*>& someAvailableActions, const GOAPGameState& aWorldState, const GOAPGameState& aGoalState);

private:
	struct Node
	{
		Node(Node* aParent, GOAPGameState aState, IGOAPAction* aAction)
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
		IGOAPAction* myAction;
		Node* myParent;

		//Only used to delete nodes after the Plan is finished
		CU::GrowingArray<Node*> myChildren;
	};

	bool BuildGraph(Node* aParent, const CU::GrowingArray<IGOAPAction*>& someAvailableActions, const GOAPGameState& aGoalState, CU::GrowingArray<Node*>& someLeaves) const;
	bool IsInState(int aState, int aCondition) const;
	int GetNewState(int aCurrentState, int someNewEffects) const;
	Node* GetBestLeaf(const CU::GrowingArray<Node*>& someLeaves) const;
	CU::GrowingArray<IGOAPAction*> GetActionsFromNode(const Node* aNode) const;
};

