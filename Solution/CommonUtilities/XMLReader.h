#pragma once
#include "tinyxml2.h"
#include "DL_Debug.h"
#include "Vector.h"
#include "CUString.h"
#include "CommonHelper.h"

//#define tinyxml2::XMLElement* tinyxml2::tinyxml2::XMLElement**

class XMLReader
{
public:
	XMLReader();
	~XMLReader();

	void OpenDocument(const CU::String& aFilePath);
	void CloseDocument();

	CU::String GetElementName(tinyxml2::XMLElement* aElement);




	/*
	---------------------------
	Normal Find Operations
	---------------------------

	These will try to find the requested element, if the element is not found
	a nullptr will be returned
	*/

	tinyxml2::XMLElement* FindFirstChild(const CU::String& aChildName);
	tinyxml2::XMLElement* FindFirstChild(tinyxml2::XMLElement* aParent) const;
	tinyxml2::XMLElement* FindFirstChild(tinyxml2::XMLElement* aParent, const CU::String& aChildName) const;
	tinyxml2::XMLElement* FindNextElement(const CU::String& aElementName);
	tinyxml2::XMLElement* FindNextElement(tinyxml2::XMLElement* aPrevElement) const;
	tinyxml2::XMLElement* FindNextElement(tinyxml2::XMLElement* aPrevElement, const CU::String& aElementName) const;





	/*
	---------------------------
	Force Find Operations
	---------------------------

	These will try to find the requested element, however it will
	not return a nullptr if the element isnt found.
	Instead it will crash and print an errormessage into
	the DebugLogger about the involved Parent, Child, Element and Document
	*/

	tinyxml2::XMLElement* ForceFindFirstChild(const CU::String& aChildName);
	tinyxml2::XMLElement* ForceFindFirstChild(tinyxml2::XMLElement* aParent) const;
	tinyxml2::XMLElement* ForceFindFirstChild(tinyxml2::XMLElement* aParent, const CU::String& aChildName) const;
	tinyxml2::XMLElement* ForceFindNextElement(const CU::String& aElementName);
	tinyxml2::XMLElement* ForceFindNextElement(tinyxml2::XMLElement* aPrevElement) const;
	tinyxml2::XMLElement* ForceFindNextElement(tinyxml2::XMLElement* aPrevElement, const CU::String& aElementName) const;




	/*
	---------------------------
	Normal Read Operations
	---------------------------

	These will try to read the attribute from the element and store the value
	into the targetvariable.
	If the attribute is not found, the targetvariable simply wont be changed,
	the program wont crash or even produce an error.
	*/

	bool ReadAttribute(const tinyxml2::XMLElement* aElementToReadFrom, const CU::String& aAttributeToRead, CU::String& aTargetVariable);
	bool ReadAttribute(const tinyxml2::XMLElement* aElementToReadFrom, const CU::String& aAttributeToRead, int& aTargetVariable);
	bool ReadAttribute(const tinyxml2::XMLElement* aElementToReadFrom, const CU::String& aAttributeToRead, float& aTargetVariable);
	bool ReadAttribute(const tinyxml2::XMLElement* aElementToReadFrom, const CU::String& aAttributeToRead, double& aTargetVariable);
	bool ReadAttribute(const tinyxml2::XMLElement* aElementToReadFrom, const CU::String& aAttributeToRead, bool& aTargetVariable);

	template<typename T>
	bool ReadAttribute(const tinyxml2::XMLElement* aElementToReadFrom, const CU::String& aAttributeToRead
			, const CU::String& aOtherAttributeToRead, CU::Vector2<T>& aTargetVariable);

	template<typename T>
	bool ReadAttribute(const tinyxml2::XMLElement* aElementToReadFrom, const CU::String& aFirst
		, const CU::String& aSecond, const CU::String& aThird, CU::Vector3<T>& aTargetVariable);




	/*
	---------------------------
	Force Read Operations
	---------------------------

	These will try to read the attribute from the element and store the value
	into the targetvariable.
	If the attribute is not found, the program will crash and print an
	error message to the DebugLogger about the involved Element, Attribute and Document.
	*/

	bool ForceReadAttribute(const tinyxml2::XMLElement* aElementToReadFrom, const CU::String& aAttributeToRead, CU::String& aTargetVariable);
	bool ForceReadAttribute(const tinyxml2::XMLElement* aElementToReadFrom, const CU::String& aAttributeToRead, int& aTargetVariable);
	bool ForceReadAttribute(const tinyxml2::XMLElement* aElementToReadFrom, const CU::String& aAttributeToRead, unsigned int& aTargetVariable);
	bool ForceReadAttribute(const tinyxml2::XMLElement* aElementToReadFrom, const CU::String& aAttributeToRead, float& aTargetVariable);
	bool ForceReadAttribute(const tinyxml2::XMLElement* aElementToReadFrom, const CU::String& aAttributeToRead, double& aTargetVariable);
	bool ForceReadAttribute(const tinyxml2::XMLElement* aElementToReadFrom, const CU::String& aAttributeToRead, bool& aTargetVariable);

	template<typename T>
	bool ForceReadAttribute(const tinyxml2::XMLElement* aElementToReadFrom, const CU::String& aAttributeToRead
		, const CU::String& aOtherAttributeToRead, CU::Vector2<T>& aTargetVariable);

	template<typename T>
	bool ForceReadAttribute(const tinyxml2::XMLElement* aElementToReadFrom, const CU::String& aFirst
		, const CU::String& aSecond, const CU::String& aThird, CU::Vector3<T>& aTargetVariable);

private:

	/*
	---------------------------
	Debug Operations
	---------------------------

	These are used to verify that the FindFirstChild and FindNextSiblingElement
	functions return valid pointers, that is, pointers that isnt nullptr.

	The ForceFind-functions all use these debugfunctions to verify that
	the requested Child/Element was found and crashes otherwise.
	*/

	void DebugFirstChild(const CU::String& aChildName);
	void DebugFirstChild(tinyxml2::XMLElement* aParent) const;
	void DebugFirstChild(tinyxml2::XMLElement* aParent, const CU::String& aChildName) const;

	void DebugNextElement(const CU::String& aChildName);
	void DebugNextElement(tinyxml2::XMLElement* aParent) const;
	void DebugNextElement(tinyxml2::XMLElement* aParent, const CU::String& aChildName) const;


	tinyxml2::XMLDocument* myDoc;
	CU::String myFilePath;
	bool myHasOpenedDoc;
};

template<typename T>
bool XMLReader::ReadAttribute(const tinyxml2::XMLElement* aElementToReadFrom, const CU::String& aAttributeToRead, const CU::String& aOtherAttributeToRead, CU::Vector2<T>& aTargetVariable)
{
	if (myHasOpenedDoc == false)
		DL_ASSERT("[XMLReader]: Tried to [ReadAttribute(Vector2<T>)] before Opening the document");

	DL_ASSERT_EXP(aElementToReadFrom != nullptr, "[XMLReader]: Tried to Read from nullptr");

	if (aElementToReadFrom == nullptr)
		return false;

	if (aElementToReadFrom->QueryFloatAttribute(aAttributeToRead.c_str(), &aTargetVariable.x) == tinyxml2::XML_NO_ERROR)
	{
		if (aElementToReadFrom->QueryFloatAttribute(aAttributeToRead.c_str(), &aTargetVariable.y) == tinyxml2::XML_NO_ERROR)
		{
			return true;
		}
	}
	return false;
}

template<typename T>
bool XMLReader::ReadAttribute(const tinyxml2::XMLElement* aElementToReadFrom, const CU::String& aFirst, const CU::String& aSecond, const CU::String& aThird, CU::Vector3<T>& aTargetVariable)
{
	if (myHasOpenedDoc == false)
		DL_ASSERT("[XMLReader]: Tried to [ReadAttribute(Vector3<T>)] before Opening the document");

	DL_ASSERT_EXP(aElementToReadFrom != nullptr, "[XMLReader]: Tried to Read from nullptr");

	if (aElementToReadFrom->QueryFloatAttribute(aFirst.c_str(), &aTargetVariable.x) == tinyxml2::XML_NO_ERROR)
	{
		if (aElementToReadFrom->QueryFloatAttribute(aSecond.c_str(), &aTargetVariable.y) == tinyxml2::XML_NO_ERROR)
		{
			if (aElementToReadFrom->QueryFloatAttribute(aThird.c_str(), &aTargetVariable.z) == tinyxml2::XML_NO_ERROR)
			{
				return true;
			}
		}
	}
	return false;
}

template<typename T>
bool XMLReader::ForceReadAttribute(const tinyxml2::XMLElement* aElementToReadFrom, const CU::String& aAttributeToRead
	, const CU::String& aOtherAttributeToRead, CU::Vector2<T>& aTargetVariable)
{
	if (myHasOpenedDoc == false)
		DL_ASSERT("[XMLReader]: Tried to [ReadAttribute(Vector2<T>)] before Opening the document");

	DL_ASSERT_EXP(aElementToReadFrom != nullptr, "[XMLReader]: Tried to Read from nullptr");

	if (aElementToReadFrom == nullptr)
		return false;

	if (aElementToReadFrom->QueryFloatAttribute(aAttributeToRead.c_str(), &aTargetVariable.x) == tinyxml2::XML_NO_ERROR)
	{
		if (aElementToReadFrom->QueryFloatAttribute(aAttributeToRead.c_str(), &aTargetVariable.y) == tinyxml2::XML_NO_ERROR)
		{
			return true;
		}
	}
	DL_ASSERT(CU::Concatenate("Failed to read Attribute: [ %s ] and [ %s ] from Element: [ %s ], in Document: [ %s ]", 
		aAttributeToRead.c_str(), aOtherAttributeToRead.c_str(), aElementToReadFrom->Name(), myFilePath.c_str()));
	return false;
}

template<typename T>
bool XMLReader::ForceReadAttribute(const tinyxml2::XMLElement* aElementToReadFrom, const CU::String& aFirst
	, const CU::String& aSecond, const CU::String& aThird, CU::Vector3<T>& aTargetVariable)
{
	if (myHasOpenedDoc == false)
		DL_ASSERT("[XMLReader]: Tried to [ReadAttribute(Vector3<T>)] before Opening the document");

	DL_ASSERT_EXP(aElementToReadFrom != nullptr, "[XMLReader]: Tried to Read from nullptr");

	if (aElementToReadFrom->QueryFloatAttribute(aFirst.c_str(), &aTargetVariable.x) == tinyxml2::XML_NO_ERROR)
	{
		if (aElementToReadFrom->QueryFloatAttribute(aSecond.c_str(), &aTargetVariable.y) == tinyxml2::XML_NO_ERROR)
		{
			if (aElementToReadFrom->QueryFloatAttribute(aThird.c_str(), &aTargetVariable.z) == tinyxml2::XML_NO_ERROR)
			{
				return true;
			}
		}
	}
	DL_ASSERT(CU::Concatenate<256>("Failed to read Attribute: [ %s ], [ %s ] and [ %s ] from Element: [ %s ], in Document: [ %s ]", 
		aFirst.c_str(), aSecond.c_str(), aThird.c_str(), aElementToReadFrom->Name(), myFilePath.c_str()));
	return false;
}