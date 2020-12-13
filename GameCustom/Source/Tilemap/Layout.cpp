#include "GamePCH.h"
#include "Tilemap.h"
#include "Layout.h"

using TT = Tilemap::TileType;

Tilemap::TileType level1Layout[] =
{
	TT::WallNW,		TT::WallNorth,	TT::WallNorth,	TT::WallNorth,	TT::WallNorth,	TT::WallNorth,	TT::WallNorth,	TT::WallNorth,	TT::WallNorth,	TT::WallNE,
	TT::WallWest,	TT::Floor,		TT::Floor,		TT::Wall,		TT::Wall,		TT::Wall,		TT::Wall,		TT::Floor,		TT::Floor,		TT::WallEast,
	TT::WallWest,	TT::Floor,		TT::Wall,		TT::Wall,		TT::Wall,		TT::Floor,		TT::Wall,		TT::Wall,		TT::Floor,		TT::WallEast,
	TT::WallWest,	TT::Wall,		TT::Floor,		TT::Wall,		TT::Wall,		TT::Wall,		TT::Wall,		TT::Wall,		TT::Wall,		TT::WallEast,
	TT::WallWest,	TT::Wall,		TT::Wall,		TT::Wall,		TT::Wall,		TT::Wall,		TT::Wall,		TT::Wall,		TT::Wall,		TT::WallEast,
	TT::WallWest,	TT::Wall,		TT::Wall,		TT::Wall,		TT::Wall,		TT::Wall,		TT::Wall,		TT::Floor,		TT::Wall,		TT::WallEast,
	TT::WallWest,	TT::Wall,		TT::Wall,		TT::Wall,		TT::Wall,		TT::Wall,		TT::Wall,		TT::Wall,		TT::Wall,		TT::WallEast,
	TT::WallWest,	TT::Floor,		TT::Wall,		TT::Wall,		TT::Floor,		TT::Wall,		TT::Wall,		TT::Wall,		TT::Floor,		TT::WallEast,
	TT::WallWest,	TT::Floor,		TT::Floor,		TT::Wall,		TT::Wall,		TT::Wall,		TT::Wall,		TT::Floor,		TT::Floor,		TT::WallEast,
	TT::WallNorth,	TT::WallNorth,	TT::WallNorth,	TT::WallNorth,	TT::WallNorth,	TT::WallNorth,	TT::WallNorth,	TT::WallNorth,	TT::WallNorth,	TT::WallNorth,
};