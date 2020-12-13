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

		if (timer > 3)
		{
			Explode();

			timer = 0.f;
			m_isActive = false;
		}

	}

	ImGui::Text("%f, %f", m_Pos.x, m_Pos.y);
}

void Bomb::Explode()
{
	int bombtile = (int)(m_Pos.y * m_pTilemap->m_MapSize.x + m_Pos.x);
	//bombtile--;

	//vertical
	if (bombtile + 10 < 100)
		m_pTilemap->m_pLayout[bombtile + 10] == Tilemap::TileType::Wall ? m_pTilemap->m_pLayout[bombtile + 10] = Tilemap::TileType::Floor : m_pTilemap->m_pLayout[bombtile + 10] = m_pTilemap->m_pLayout[bombtile + 10];
	
	if (bombtile + 20 < 100)
		m_pTilemap->m_pLayout[bombtile + 20] == Tilemap::TileType::Wall ? m_pTilemap->m_pLayout[bombtile + 20] = Tilemap::TileType::Floor : m_pTilemap->m_pLayout[bombtile + 20] = m_pTilemap->m_pLayout[bombtile + 20];
	
	if (bombtile - 10 > 0)
		m_pTilemap->m_pLayout[bombtile - 10] == Tilemap::TileType::Wall ? m_pTilemap->m_pLayout[bombtile - 10] = Tilemap::TileType::Floor : m_pTilemap->m_pLayout[bombtile - 10] = m_pTilemap->m_pLayout[bombtile - 10];
	
	if (bombtile - 20 > 0)
		m_pTilemap->m_pLayout[bombtile - 20] == Tilemap::TileType::Wall ? m_pTilemap->m_pLayout[bombtile - 20] = Tilemap::TileType::Floor : m_pTilemap->m_pLayout[bombtile - 20] = m_pTilemap->m_pLayout[bombtile - 20];

	SetCanDraw(false);

	//horizontal
	if (bombtile + 1 < 100)
		m_pTilemap->m_pLayout[bombtile + 1] == Tilemap::TileType::Wall ? m_pTilemap->m_pLayout[bombtile + 1] = Tilemap::TileType::Floor : m_pTilemap->m_pLayout[bombtile + 1] = m_pTilemap->m_pLayout[bombtile + 1];

	if (bombtile + 2 < 100)
		m_pTilemap->m_pLayout[bombtile + 2] == Tilemap::TileType::Wall ? m_pTilemap->m_pLayout[bombtile + 2] = Tilemap::TileType::Floor : m_pTilemap->m_pLayout[bombtile + 2] = m_pTilemap->m_pLayout[bombtile + 2];

	if (bombtile - 1 > 0)
		m_pTilemap->m_pLayout[bombtile - 1] == Tilemap::TileType::Wall ? m_pTilemap->m_pLayout[bombtile - 1] = Tilemap::TileType::Floor : m_pTilemap->m_pLayout[bombtile - 1] = m_pTilemap->m_pLayout[bombtile - 1];

	if (bombtile - 2 > 0)
		m_pTilemap->m_pLayout[bombtile - 2] == Tilemap::TileType::Wall ? m_pTilemap->m_pLayout[bombtile - 2] = Tilemap::TileType::Floor : m_pTilemap->m_pLayout[bombtile - 2] = m_pTilemap->m_pLayout[bombtile - 2];

}

void Bomb::SetIsActive(bool active)
{
	m_isActive = active;
}
