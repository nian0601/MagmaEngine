#include "stdafx.h"

#include "Node.h"
#include <XMLReader.h>

namespace Magma
{
	Node::Node()
		: myGraph(nullptr)
		, myIsInitNode(false)
		, myUID(-1)
		, myFileName("not set")
	{
	}


	Node::Node(XMLReader& aReader, tinyxml2::XMLElement* aNodeElement, NodeGraph* aGraph)
		: Node()
	{
		myGraph = aGraph;

		tinyxml2::XMLElement* nameElement = aReader.ForceFindFirstChild(aNodeElement, "Name");
		tinyxml2::XMLElement* uidElement = aReader.ForceFindFirstChild(aNodeElement, "UID");
		tinyxml2::XMLElement* filePathElement = aReader.ForceFindFirstChild(aNodeElement, "FilePath");
		tinyxml2::XMLElement* connectionsElement = aReader.ForceFindFirstChild(aNodeElement, "Connections");


		myUID = std::atoll(uidElement->GetText());
		myFileName = filePathElement->GetText();

		CU::String nodeName = nameElement->GetText();
		if (nodeName == "script init")
		{
			myIsInitNode = true;
		}
		

	}

	Node::~Node()
	{
	}

	void Node::Execute()
	{

	}

}