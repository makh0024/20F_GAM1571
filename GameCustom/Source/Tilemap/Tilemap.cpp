#include "GamePCH.h"
#include "Layout.h"
#include "../Characters/Shapes.h"
#include "../Characters/Player.h"

#include "Tilemap.h"

using namespace fw;

Tilemap::Tilemap(int width, int height, const TileType* pLayout, fw::Mesh* mesh, fw::ShaderProgram* shader, fw::Texture* texture, fw::Spritesheet* spriteSheet)
{
	m_MapSize.x = (float)width;
	m_MapSize.y = (float)height;


	m_pLayout = new TileType[width * height];

	/*for (int i = 0; i < width * height; i++)
	{
		m_pLayout[i] = pLayout[i];
	}*/

	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			int index = y * width + x;
			int flippedIndex = (height - y - 1) * width + x;

			m_pLayout[flippedIndex] = pLayout[index];
		}
	}

	m_TilePos = fw::vec2(5.0f, 5.0f);
	m_Color = fw::vec4::White(1.0f);

	m_pTileMesh = mesh;
	m_pShader = shader;
	m_pTexture = texture;

	m_pSpritesheet = spriteSheet;

	m_pTileSprite = m_pSpritesheet->GetSpriteInfo("Floor");

	m_pTileProperties.push_back(TileProperties(m_pSpritesheet->GetSpriteInfo("Floor"), true, true));
	m_pTileProperties.push_back(TileProperties(m_pSpritesheet->GetSpriteInfo("Wall"),    false, true));
	m_pTileProperties.push_back(TileProperties(m_pSpritesheet->GetSpriteInfo("Wall-S"),  false, false));
	m_pTileProperties.push_back(TileProperties(m_pSpritesheet->GetSpriteInfo("Wall-N"),  false, false));
	m_pTileProperties.push_back(TileProperties(m_pSpritesheet->GetSpriteInfo("Wall-W"),  false, false));
	m_pTileProperties.push_back(TileProperties(m_pSpritesheet->GetSpriteInfo("Wall-E"),  false, false));
	m_pTileProperties.push_back(TileProperties(m_pSpritesheet->GetSpriteInfo("Wall-NE"), false, false));
	m_pTileProperties.push_back(TileProperties(m_pSpritesheet->GetSpriteInfo("Wall-NW"), false, false));
	m_pTileProperties.push_back(TileProperties(m_pSpritesheet->GetSpriteInfo("Wall-SE"), false, false));
	m_pTileProperties.push_back(TileProperties(m_pSpritesheet->GetSpriteInfo("Wall-SW"), false, false));
	//m_pTileProperties.push_back(TileProperties(m_pSpritesheet->GetSpriteInfo("Floor"),   true));
}

Tilemap::~Tilemap()
{
	delete[] m_pLayout;
}

void Tilemap::SendPlayerPos(fw::vec2 playerPos)
{
	m_PlayerPos = playerPos;
}

fw::vec2 Tilemap::GetPosAtTile(int tileNum)
{
	return m_TilePos * m_TileSize;
}

fw::vec2 Tilemap::CurrentTileAt(fw::vec2 tilePos)
{
	fw::vec2 TtilePos = vec2(tilePos.x / m_TileSize.x, tilePos.y / m_TileSize.y);

	return TtilePos;
}

bool Tilemap::IsTileWalkableAtTilePos(int x, int y)
{
	if (x < 0 || x >= (int)m_MapSize.x || y < 0 || y >= (int)m_MapSize.y)
		return false;

	//return m_pLayout[y * (int)m_MapSize.x + x] == TileType::Floor ? true : false;

	return m_pTileProperties.at(int(m_pLayout[y * (int)m_MapSize.x + x])).bIsWalkable;
}

void Tilemap::Draw()
{
	for (int y = 0; y < m_MapSize.y; y++)
	{
		for (int x = 0; x < m_MapSize.x; x++)
		{
			m_TilePos = fw::vec2((float)x, (float)(y/*m_MapSize.y -y -1*/));

			int TileIndex = y * (int)m_MapSize.x + x;

			TileType type = m_pLayout[TileIndex];

			TileProperties properties = m_pTileProperties[(int)type];

			m_pTileMesh->Draw(m_TilePos * m_TileSize, m_TileSize, m_PlayerPos, m_Color, m_pShader, m_pTexture, properties.m_UVScale, properties.m_UVOffset);

			/*if (properties.bIsWalkable == false)
			{
				float rightTileWall = m_TilePos.x * m_TileSize.x + (m_TileSize.x / 2);
				float leftTileWall = m_TilePos.x * m_TileSize.x - (m_TileSize.x / 2);
				float topTileWall = m_TilePos.y * m_TileSize.y + (m_TileSize.y / 2);
				float bottomTileWall = m_TilePos.y * m_TileSize.y - (m_TileSize.y / 2);

				float playerLeftWall = m_pPlayer->GetPosition().x - 0.2f;
				float playerRightWall = m_pPlayer->GetPosition().x + 0.2f;
				float playerTopWall = m_pPlayer->GetPosition().y + 0.2f;
				float playerBottomWall = m_pPlayer->GetPosition().y - 0.2f;

				if ((playerLeftWall < rightTileWall && playerRightWall > leftTileWall &&
					 playerBottomWall < topTileWall  && playerTopWall > bottomTileWall))
				{
					fw::vec2 playerpos = m_pPlayer->GetPosition();
					fw::vec2 tilepos = m_TilePos * m_TileSize;
					fw::vec2 newpos = (playerpos - tilepos).Normalized();

					m_pPlayer->SetPosition(newpos * ((m_TileSize.x / 2) + 0.2f) + tilepos);
				}
			}*/
		}
	}
}
