#include "stdafx.h"

#include "AssetContainer.h"
#include <CommonHelper.h>
#include "Font.h"
#include "Texture.h"

#include <istream>

namespace Magma
{
	void CharData::LoadFromLine(const std::string& aLine, const CU::Vector2<float>& aTextureSize)
	{
		std::string id = LoadToken(aLine, "id=");
		std::string x = LoadToken(aLine, "x=");
		std::string y = LoadToken(aLine, "y=");
		std::string width = LoadToken(aLine, "width=");
		std::string height = LoadToken(aLine, "height=");
		std::string xoffset = LoadToken(aLine, "xoffset=");
		std::string yoffset = LoadToken(aLine, "yoffset=");
		std::string xadvance = LoadToken(aLine, "xadvance=");

		myID = static_cast<char>(atoi(id.c_str()));
		myX = atoi(x.c_str());
		myY = atoi(y.c_str());
		myWidth = atoi(width.c_str());
		myHeight = atoi(height.c_str());
		myXOffset = static_cast<float>(atof(xoffset.c_str()));
		myYOffset = static_cast<float>(atof(yoffset.c_str()));
		myXAdvance = static_cast<float>(atof(xadvance.c_str()));

		myTopLeftUV.x = myX;
		myTopLeftUV.y = myY;
		myBottomRightUV.x = myTopLeftUV.x + myWidth;
		myBottomRightUV.y = myTopLeftUV.y + myHeight;

		myTopLeftUV /= aTextureSize;
		myBottomRightUV /= aTextureSize;
	}


	std::string CharData::LoadToken(const std::string& aLine, const std::string& aToken)
	{
		int startIndex = aLine.find(aToken);
		startIndex += aToken.length();
		int secondIndex = startIndex;
		while (aLine[secondIndex] != ' ')
			++secondIndex;

		return aLine.substr(startIndex, secondIndex - startIndex);
	}


	Font::Font()
		: myTexture(nullptr)
		, myScale(0.33f)
		, myMaxHeight(0.f)
	{

	}

	void Font::LoadFromFile(const CU::String& aFilePath, AssetContainer& aAssetContainer)
	{
		CU::String texturePath = aFilePath;
		myTexture = aAssetContainer.LoadTexture(texturePath);
		CU::Vector2<float> textureSize = myTexture->GetSize();

		CU::String txtPath = CU::ReplaceExtension(aFilePath, "txt");

		std::ifstream stream;
		stream.open(txtPath.c_str());
		if (!stream.is_open())
			return;

		std::string line;
		std::getline(stream, line); //first line is just the name of the font, dont care
		std::getline(stream, line); //the second like is the number of characers in the file ("chars count=191"), dont care

		int counter = 0;
		while (std::getline(stream, line))
		{
			CharData data;
			data.LoadFromLine(line, textureSize);
			myCharacters[data.myID] = data;

			if (data.myHeight > myMaxHeight)
				myMaxHeight = data.myHeight;
		}

		
	}

	const Magma::CharData& Font::GetCharData(char aCharacter) const
	{
		if (myCharacters.KeyExists(aCharacter))
			return myCharacters.Get(aCharacter);

		DL_ASSERT("Failed to GetCharData from Font");
		return myEmptyCharData;
	}

}