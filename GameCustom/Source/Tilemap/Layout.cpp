#include "GamePCH.h"
#include "Tilemap.h"
#include "Layout.h"

using TT = Tilemap::TileType;

const Tilemap::TileType level1Layout[] =
{
	TT::Wall, TT::Wall, TT::Wall, TT::Wall, TT::Wall, TT::Wall, TT::Wall, TT::Wall, TT::Wall, TT::Wall,
	TT::Wall, TT::Floor,TT::Floor,TT::Floor,TT::Floor,TT::Floor,TT::Floor,TT::Floor,TT::Floor,TT::Wall,
	TT::Wall, TT::Floor,TT::Floor,TT::Floor,TT::Floor,TT::Floor,TT::Wall ,TT::Floor,TT::Floor,TT::Wall,
	TT::Wall, TT::Floor,TT::Floor,TT::Floor,TT::Floor,TT::Floor,TT::Floor,TT::Floor,TT::Floor,TT::Wall,
	TT::Wall, TT::Floor,TT::Floor,TT::Floor,TT::Floor,TT::Floor,TT::Floor,TT::Floor,TT::Floor,TT::Wall,
	TT::Wall, TT::Floor,TT::Floor,TT::Floor,TT::Floor,TT::Floor,TT::Floor,TT::Floor,TT::Floor,TT::Wall,
	TT::Wall, TT::Floor,TT::Floor,TT::Wall ,TT::Floor,TT::Floor,TT::Floor,TT::Floor,TT::Floor,TT::Wall,
	TT::Wall, TT::Floor,TT::Floor,TT::Floor,TT::Floor,TT::Floor,TT::Floor,TT::Floor,TT::Floor,TT::Wall,
	TT::Wall, TT::Floor,TT::Floor,TT::Floor,TT::Floor,TT::Floor,TT::Floor,TT::Floor,TT::Floor,TT::Wall,
	TT::Wall, TT::Wall, TT::Wall, TT::Wall, TT::Wall, TT::Wall, TT::Wall, TT::Wall, TT::Wall, TT::Wall,
};