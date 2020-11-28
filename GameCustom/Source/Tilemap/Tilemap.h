#pragma once

struct TileProperties
{
	bool bIsWalkable;
	fw::vec2 m_UVScale;
	fw::vec2 m_UVOffset;

	TileProperties(fw::Sprite* SpriteInfo, bool walkable)
	{
		bIsWalkable = walkable;

		m_UVScale = fw::vec2(SpriteInfo->m_ScaleX / 256.0f, SpriteInfo->m_ScaleY / 128.0f);
		m_UVOffset = fw::vec2(SpriteInfo->m_OffsetX / 256.0f, SpriteInfo->m_OffsetY / 128.0f);
	}
};

class Tilemap
{
public:
	enum class TileType
	{
		Floor = 0,
		Wall = 1,
		WallNorth = 2,
		WallSouth = 3,
		WallEast = 4,
		WallWest = 5,
		WallNE = 6,
		WallNW = 7,
		WallSE = 8,
		WallSW = 9,
		NumTypes
	};

	Tilemap(int width, int height, const TileType* pLayout);
	void SetTilemap();
	~Tilemap();

	void SendPlayerPos(fw::vec2 playerPos);

	void Draw();
protected:
	std::vector<TileProperties> m_pTileProperties;
	TileType* m_pLayout;

	fw::Spritesheet* m_pSpritesheet = nullptr;
	fw::Sprite* m_pTileSprite;

private:
	fw::Mesh* m_pTileMesh;
	fw::vec2 m_TilePos;
	fw::vec4 m_Color = fw::vec4(0, 0, 0, 0);

	fw::ShaderProgram* m_pShader = nullptr;
	fw::Texture* m_pTexture = nullptr;
	
	fw::vec2 m_MapSize;
	
	fw::vec2 m_TileSize = fw::vec2(1.5f, 1.5f);

	fw::vec2 m_UVScale = fw::vec2(1, 1);
	fw::vec2 m_UVOffset = fw::vec2(0, 0);

	fw::vec2 m_PlayerPos;
};