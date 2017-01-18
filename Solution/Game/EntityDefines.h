#pragma once

enum eResourceType
{
	INVALID = -1,
	TREE,
	WATER,
	_RESOURCE_COUNT,
};

enum class eEntityState
{
	CAN_GATHER_WOOD,
	CAN_GATHER_WATER,
	HAS_AXE,
	HAS_BUCKET,
	HAS_WATER,
	HAS_WOOD,
	HAS_DRINK,
	HAS_GLASS,
	_COUNT,
};

enum class eWorldState
{
	HAS_WOOD_ON_STOCKPILE,
	HAS_WATER_ON_STOCKPILE,
	_COUNT,
};