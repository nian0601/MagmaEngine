#pragma once

enum eResourceType
{
	INVALID,
	TREE,
	WATER,
	_COUNT,
};

enum eEntityState
{
	CAN_GATHER_WOOD,
	CAN_GATHER_WATER,
	HAS_AXE,
	HAS_BUCKET,
	HAS_WATER,
	HAS_WOOD,
	HAS_DRINK,
	HAS_GLASS,
	_STATE_COUNT,
};