#include "GamePCH.h"

#include "Player.h"
using namespace fw;

Player::Player(float x, float y, std::string Name, Mesh* Mesh, ShaderProgram* Shader, GameCore* pGameCore) : fw::GameObject (x, y, Name, Mesh, Shader, pGameCore)
{
	m_pFramework = m_pGameCore->GetFramework();
}

Player::~Player()
{
}

void Player::Update(float deltaTime)
{
	if (m_pFramework->IsKeyDown('W') || m_pFramework->IsKeyDown(VK_UP))
	{
		m_Pos.y += 2.0f * deltaTime;
	}

	if (m_pFramework->IsKeyDown('A') || m_pFramework->IsKeyDown(VK_LEFT))
	{
		m_Pos.x -= 2.0f * deltaTime;
	}

	if (m_pFramework->IsKeyDown('S') || m_pFramework->IsKeyDown(VK_DOWN))
	{
		m_Pos.y -= 2.0f * deltaTime;
	}

	if (m_pFramework->IsKeyDown('D') || m_pFramework->IsKeyDown(VK_RIGHT))
	{
		m_Pos.x += 2.0f * deltaTime;
	}

	ImGui::DragFloat2("Position", &m_Pos.x, 0.1f);
}
