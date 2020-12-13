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

		if (timer > 2)
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
	SetCanDraw(false);

	//vertical
	for (int i = 10; i < 21; i += 10)
	{
		if (bombtile + i < 100)
			m_pTilemap->m_pLayout[bombtile + i] == Tilemap::TileType::Wall ? m_pTilemap->m_pLayout[bombtile + i] = Tilemap::TileType::Floor : m_pTilemap->m_pLayout[bombtile + i] = m_pTilemap->m_pLayout[bombtile + i];
		
		if (bombtile - 10 > 0)
			m_pTilemap->m_pLayout[bombtile - i] == Tilemap::TileType::Wall ? m_pTilemap->m_pLayout[bombtile - i] = Tilemap::TileType::Floor : m_pTilemap->m_pLayout[bombtile - i] = m_pTilemap->m_pLayout[bombtile - i];
	}
	
	//horizontal
	for (int i = 1; i < 3; i++)
	{
		if (bombtile + i < 100)
			m_pTilemap->m_pLayout[bombtile + i] == Tilemap::TileType::Wall ? m_pTilemap->m_pLayout[bombtile + i] = Tilemap::TileType::Floor : m_pTilemap->m_pLayout[bombtile + i] = m_pTilemap->m_pLayout[bombtile + i];
		
		if (bombtile - i > 0)
			m_pTilemap->m_pLayout[bombtile - i] == Tilemap::TileType::Wall ? m_pTilemap->m_pLayout[bombtile - i] = Tilemap::TileType::Floor : m_pTilemap->m_pLayout[bombtile - i] = m_pTilemap->m_pLayout[bombtile - i];
	}
	

}

void Bomb::SetIsActive(bool active)
{
	m_isActive = active;
}
