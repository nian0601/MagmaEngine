#include "stdafx.h"

#include "Node.h"
#include "NodeGraph.h"
#include <XMLReader.h>

namespace Magma
{
	NodeGraph::NodeGraph()
	{
	}


	NodeGraph::NodeGraph(const CU::String& aFilePath)
	{
		XMLReader reader;
		reader.OpenDocument(aFilePath.c_str());

		tinyxml2::XMLElement* nodeTreeElement = reader.ForceFindFirstChild("NodeTree");
		tinyxml2::XMLElement* nodeElement = nullptr;

		Node* rootNode = nullptr;

		for (nodeElement = reader.FindFirstChild(nodeTreeElement, "Node"); nodeElement != nullptr; nodeElement = reader.FindNextElement(nodeElement, "Node"))
		{
			Node* node = new Node(reader, nodeElement, this);
			myNodes[node->GetUID()] = node;

			if (node->IsInitNode())
				rootNode = node;
		}

		reader.CloseDocument();

		rootNode->Execute();
	}

	NodeGraph::~NodeGraph()
	{
	}
}