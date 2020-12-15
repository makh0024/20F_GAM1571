#include "GamePCH.h"
#include "Tilemap/Tilemap.h"

#include "Bomb.h"


Bomb::Bomb(float x, float y, std::string Name, fw::Mesh* Mesh, fw::ShaderProgram* Shader, fw::vec4 color, fw::GameCore* pGameCore, fw::vec2 bombScale, Tilemap* pTilemap) : 
	fw::GameObject(x, y, Name, Mesh, Shader, color, pGameCore, Type::Bomb, bombScale)
{
	m_pTilemap = pTilemap;

	timer = 0.f;

	m_isActive = false;

	SetCanDraw(false);
}

Bomb::~Bomb()
{
}

void Bomb::Update(float deltaTime)
{
	if (m_isActive)
	{
		timer += deltaTime;

		SetCanDraw(true);

		if (timer > 4)
		{
			Explode();

			timer = 0.f;
			m_isActive = false;
		}

		for (int i = 1; i < 3; i++)
		{
			explodedtiles[0] = (int)(m_Pos.y * m_pTilemap->m_MapSize.x + m_Pos.x);

			//vertical
			explodedtiles[i] = (int)(m_Pos.y * m_pTilemap->m_MapSize.x + m_Pos.x) + 10 * i;
			explodedtiles[i + 2] = (int)(m_Pos.y * m_pTilemap->m_MapSize.x + m_Pos.x) - 10 * i;

			//horizontal
			explodedtiles[i + 4] = (int)(m_Pos.y * m_pTilemap->m_MapSize.x + m_Pos.x) + 1 * i;
			explodedtiles[i + 6] = (int)(m_Pos.y * m_pTilemap->m_MapSize.x + m_Pos.x) - 1 * i;
		}

	}

	ImGui::Text("%f, %f", m_Pos.x, m_Pos.y);
}

void Bomb::Explode()
{	

	int bombtile = (int)(m_Pos.y * m_pTilemap->m_MapSize.x + m_Pos.x);
	//bombtile--;
	SetCanDraw(false);

	int bombtilex = bombtile % (int)m_pTilemap->m_MapSize.x;
	int bombtiley = bombtile / (int)m_pTilemap->m_MapSize.y;

	int range = 2;

	//vertical
	for (int i = 0; i < range; i++)
	{
		int tocheck = bombtile + (i + 1) * (int)(m_pTilemap->m_MapSize.y);

		if (bombtiley + i + 1 < m_pTilemap->m_MapSize.y)
			m_pTilemap->m_pTileProperties[(int)m_pTilemap->m_pLayout[tocheck]].isDestructible == true ? m_pTilemap->m_pLayout[tocheck] = Tilemap::TileType::Floor : m_pTilemap->m_pLayout[tocheck] = m_pTilemap->m_pLayout[tocheck];
		
		if (m_pTilemap->m_pTileProperties[(int)m_pTilemap->m_pLayout[tocheck]].isDestructible != true)
			break;

	}

	for (int i = 0; i < range; i++)
	{
		int tocheck = bombtile - (i + 1) * (int)(m_pTilemap->m_MapSize.y);

		if (bombtiley + i + 1 < m_pTilemap->m_MapSize.y)
			m_pTilemap->m_pTileProperties[(int)m_pTilemap->m_pLayout[tocheck]].isDestructible == true ? m_pTilemap->m_pLayout[tocheck] = Tilemap::TileType::Floor : m_pTilemap->m_pLayout[tocheck] = m_pTilemap->m_pLayout[tocheck];
		
		if (m_pTilemap->m_pTileProperties[(int)m_pTilemap->m_pLayout[tocheck]].isDestructible != true)
			break;
	}

	//horizontal
	for (int i = 0; i < range; i++)
	{
		int tocheck = bombtile + (i + 1);

		if (bombtilex + i + 1 < m_pTilemap->m_MapSize.x)
			m_pTilemap->m_pTileProperties[(int)m_pTilemap->m_pLayout[tocheck]].isDestructible == true ? m_pTilemap->m_pLayout[tocheck] = Tilemap::TileType::Floor : m_pTilemap->m_pLayout[tocheck] = m_pTilemap->m_pLayout[tocheck];
		
		if (m_pTilemap->m_pTileProperties[(int)m_pTilemap->m_pLayout[tocheck]].isDestructible != true)
			break;
	}

	for (int i = 0; i < range; i++)
	{
		int tocheck = bombtile - (i + 1);

		if (bombtilex - i + 1 < m_pTilemap->m_MapSize.x)
			m_pTilemap->m_pTileProperties[(int)m_pTilemap->m_pLayout[tocheck]].isDestructible == true ? m_pTilemap->m_pLayout[tocheck] = Tilemap::TileType::Floor : m_pTilemap->m_pLayout[tocheck] = m_pTilemap->m_pLayout[tocheck];
	
		if (m_pTilemap->m_pTileProperties[(int)m_pTilemap->m_pLayout[tocheck]].isDestructible != true)
			break;
	}

	hasexploded = true;
}

void Bomb::SetIsActive(bool active)
{
	m_isActive = active;
}
