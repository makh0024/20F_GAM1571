#include "GamePCH.h"
#include "Tilemap.h"

#include "Layout.h"

using TT = Tilemap::TileType;

const Tilemap::TileType level1Layout[] =
{
	TT::WallNW,		TT::WallNorth,	TT::WallNorth,	TT::WallNorth,	TT::WallNorth,	TT::WallNorth,	TT::WallNorth,	TT::WallNorth,	TT::WallNorth,	TT::WallNE,
	TT::WallWest, TT::Floor,	TT::Floor,	TT::WallEast,	TT::Floor,	TT::Floor,	TT::WallEast,	TT::Floor,	TT::Floor,	TT::WallEast,
	TT::WallWest, TT::Floor,	TT::Floor,	TT::Floor,	TT::Floor,	TT::Floor,	TT::WallEast,	TT::Floor,	TT::Floor,	TT::WallEast,
	TT::WallWest, TT::Floor,	TT::Floor,	TT::WallEast,	TT::Floor,	TT::Floor,	TT::Floor,	TT::Floor,	TT::Floor,	TT::WallEast,
	TT::WallWest, TT::WallNorth,	TT::Floor,	TT::WallSE,	TT::Floor,	TT::Floor,	TT::WallSW,	TT::Floor,	TT::WallNorth,	TT::WallEast,
	TT::WallWest, TT::Floor,	TT::Floor,	TT::Floor,	TT::Floor,	TT::Floor,	TT::Floor,	TT::Floor,	TT::Floor,	TT::WallEast,
	TT::WallWest, TT::WallNorth,	TT::Floor,	TT::WallNE,	TT::Floor,	TT::Floor,	TT::WallNW,	TT::Floor,	TT::WallNorth,	TT::WallEast,
	TT::WallWest, TT::Floor,	TT::Floor,	TT::Floor,	TT::Floor,	TT::Floor,	TT::Floor,	TT::Floor,	TT::Floor,	TT::WallEast,
	TT::WallWest, TT::Floor,	TT::Floor,	TT::WallEast,	TT::Floor,	TT::Floor,	TT::WallWest,	TT::Floor,	TT::Floor,	TT::WallEast,
	TT::WallNorth,		TT::WallNorth,	 TT::WallNorth,		TT::WallNorth,	TT::WallNorth,	TT::WallNorth,	TT::WallNorth,	 TT::WallNorth,		TT::WallNorth,	 TT::WallNorth,
};