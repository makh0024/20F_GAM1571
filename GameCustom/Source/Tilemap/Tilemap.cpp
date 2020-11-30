#include "GamePCH.h"
#include "Layout.h"
#include "../Characters/Shapes.h"
#include "../Characters/Player.h"

#include "Tilemap.h"

using namespace fw;

Tilemap::Tilemap(int width, int height, const TileType* pLayout, Player* player)
{
	m_MapSize.x = (float)width;
	m_MapSize.y = (float)height;

	m_pPlayer = player;

	m_pLayout = new TileType[width * height];

	for (int i = 0; i < width * height; i++)
	{
		m_pLayout[i] = pLayout[i];
	}

	m_TilePos = fw::vec2(5.0f, 5.0f);
	m_Color = fw::vec4::White(1.0f);

	m_pTileMesh = new fw::Mesh(meshPrimType_Sprite, meshNumVerts_Sprite, meshAttribs_Sprite);;
	m_pShader = new fw::ShaderProgram("Data/Basic.vert", "Data/Basic.frag");
	m_pTexture = new fw::Texture("Data/Textures/Bomberman.png");

	m_pSpritesheet = new fw::Spritesheet("Data/Textures/Bomberman.json");

	m_pTileSprite = m_pSpritesheet->GetSpriteInfo("Floor");

	//m_pTileProperties.resize((int)TileType::NumTypes);
	//m_pTileProperties[(int)TileType::Floor] = TileProperties(m_pSpritesheet->GetSpriteInfo("Floor"), true);
	//m_pTileProperties[(int)TileType::Wall] = TileProperties(m_pSpritesheet->GetSpriteInfo("Wall"), true);

	m_pTileProperties.push_back(TileProperties(m_pSpritesheet->GetSpriteInfo("Floor"), true));
	m_pTileProperties.push_back(TileProperties(m_pSpritesheet->GetSpriteInfo("Wall"),    false));
	m_pTileProperties.push_back(TileProperties(m_pSpritesheet->GetSpriteInfo("Wall-S"),  false));
	m_pTileProperties.push_back(TileProperties(m_pSpritesheet->GetSpriteInfo("Wall-N"),  false));
	m_pTileProperties.push_back(TileProperties(m_pSpritesheet->GetSpriteInfo("Wall-W"),  false));
	m_pTileProperties.push_back(TileProperties(m_pSpritesheet->GetSpriteInfo("Wall-E"),  false));
	m_pTileProperties.push_back(TileProperties(m_pSpritesheet->GetSpriteInfo("Wall-NE"), false));
	m_pTileProperties.push_back(TileProperties(m_pSpritesheet->GetSpriteInfo("Wall-NW"), false));
	m_pTileProperties.push_back(TileProperties(m_pSpritesheet->GetSpriteInfo("Wall-SE"), false));
	m_pTileProperties.push_back(TileProperties(m_pSpritesheet->GetSpriteInfo("Wall-SW"), false));
}

Tilemap::~Tilemap()
{
	delete m_pTileMesh;
	delete m_pShader;
	delete m_pTexture;

	delete m_pSpritesheet;

	delete[] m_pLayout;
}

void Tilemap::SendPlayerPos(fw::vec2 playerPos)
{
	m_PlayerPos = playerPos;
}

void Tilemap::Draw()
{
	for (int y = 0; y < m_MapSize.y; y++)
	{
		for (int x = 0; x < m_MapSize.x; x++)
		{
			m_TilePos = fw::vec2((float)x, (float)(m_MapSize.y -y -1));

			int TileIndex = y * (int)m_MapSize.x + x;

			TileType type = m_pLayout[TileIndex];

			TileProperties properties = m_pTileProperties[(int)type];

			m_pTileMesh->Draw(m_TilePos * m_TileSize, m_TileSize, m_PlayerPos, m_Color, m_pShader, m_pTexture, properties.m_UVScale, properties.m_UVOffset);

			//if (properties.bIsWalkable == false)
			//{
			//	float rightTileWall = m_TilePos.x + (m_TileSize.x / 2);
			//	float leftTileWall = m_TilePos.x - (m_TileSize.x / 2);
			//	float topTileWall = m_TilePos.y + (m_TileSize.y / 2);
			//	float bottomTileWall = m_TilePos.y - (m_TileSize.y / 2);

			//	if ((m_pPlayer->GetPosition().x - 0.5f < rightTileWall || m_pPlayer->GetPosition().x + 0.5f > leftTileWall &&
			//		 m_pPlayer->GetPosition().y - 0.5f < topTileWall   || m_pPlayer->GetPosition().y + 0.5f > bottomTileWall))
			//	{
			//		m_pPlayer->SetPosition(fw::vec2(7.5f, 7.5f)); //de boog
			//	}
			//}
		}
	}
}
