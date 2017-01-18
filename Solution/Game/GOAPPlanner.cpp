#include "stdafx.h"

#include "GOAPPlan.h"
#include "GOAPPlanner.h"
#include "GOAPAction.h"

#include "GatherWaterAction.h"
#include "GatherWoodAction.h"

GOAPPlanner::GOAPPlanner()
{
}


GOAPPlanner::~GOAPPlanner()
{
}

GOAPPlan* GOAPPlanner::CreatePlan(const CU::GrowingArray<GOAPAction*>& someAvailableActions, const GOAPGameState& aWorldState, const GOAPGameState& aGoalState)
{
	Node* firstNode = new Node(nullptr, aWorldState, nullptr);
	CU::GrowingArray<Node*> leaveNodes(4);

	bool success = BuildGraph(firstNode, someAvailableActions, aGoalState, leaveNodes);

	if (!success)
		return nullptr;

	Node* bestNode = GetBestLeaf(leaveNodes);

	CU::GrowingArray<GOAPAction*> planActions = GetActionsFromNode(bestNode);

	//This will delete all the nodes, since this is the top-most node in the heirachy
	//and every node will delete its children
	delete firstNode;
	firstNode = nullptr;

	return new GOAPPlan(planActions);
}

bool GOAPPlanner::BuildGraph(Node* aParent, const CU::GrowingArray<GOAPAction*>& someAvailableActions, const GOAPGameState& aGoalState, CU::GrowingArray<Node*>& someLeaves) const
{
	bool foundPlan = false;

	for (int i = 0; i < someAvailableActions.Size(); ++i)
	{
		GOAPAction* action = someAvailableActions[i];

		//If our current WorldState fullfills the PreConditions, then we can use that action
		if (aParent->myState.Contains(action->GetPreConditions()))
		{
			//Update the World, so that it reflects what it would look like after we execute the action
			GOAPGameState updatedState;
			aParent->myState.GetNewState(action->GetEffects(), updatedState);

			Node* child = new Node(aParent, updatedState, action);

			//Is the world fullfilling our goals now?
			if (updatedState.Contains(aGoalState))
			{
				//If so we have found a solution
				someLeaves.Add(child);
				foundPlan = true;
			}
			else
			{
				//Else we'll have to dig deeper

				//Remove the current action, so that we dont get multiple actions of the same
				//kind, unless it was inteneded (by adding it multiple times in the actions-list)
				CU::GrowingArray<GOAPAction*> actionSubSet(someAvailableActions);
				actionSubSet.RemoveCyclic(action);

				if (BuildGraph(child, actionSubSet, aGoalState, someLeaves))
					foundPlan = true;
			}
		}
	}

	return foundPlan;
}

bool GOAPPlanner::IsInState(int aState, int aCondition) const
{
	return (aState & aCondition) > 0;
}

int GOAPPlanner::GetNewState(int aCurrentState, int someNewEffects) const
{
	return aCurrentState | someNewEffects;
}

GOAPPlanner::Node* GOAPPlanner::GetBestLeaf(const CU::GrowingArray<Node*>& someLeaves) const
{
	Node* bestNode = nullptr;
	int bestCount = INT_MAX;

	for (int i = 0; i < someLeaves.Size(); ++i)
	{
		int currCount = 0;
		Node* currNode = someLeaves[i];

		while (currNode)
		{
			++currCount;
			currNode = currNode->myParent;
		}

		if (currCount < bestCount)
		{
			bestCount = currCount;
			bestNode = someLeaves[i];
		}
	}

	return bestNode;
}

CU::GrowingArray<GOAPAction*> GOAPPlanner::GetActionsFromNode(const Node* aNode) const
{
	CU::GrowingArray<GOAPAction*> actions(8);

	const Node* current = aNode;
	while (current && current->myAction)
	{
		actions.Add(current->myAction);
		current = current->myParent;
	}

	return actions;
}