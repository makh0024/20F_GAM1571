#include "GamePCH.h"

#include "Player.h"
using namespace fw;

#include "PlayerController.h"

Player::Player(float x, float y, std::string Name, PlayerController* pPlayerController, Mesh* Mesh, ShaderProgram* Shader, fw::vec4 color, GameCore* pGameCore) : fw::GameObject (x, y, Name, Mesh, Shader, color, pGameCore)
{
	m_pFramework = m_pGameCore->GetFramework();
	m_pPlayerController = pPlayerController;
}

Player::~Player()
{
}

void Player::Update(float deltaTime)
{
	if (m_pPlayerController->IsUpHeld() == true)
	{
		m_Pos.y += 2.0f * deltaTime;
	}

	if (m_pPlayerController->IsLeftHeld() == true)
	{
		m_Pos.x -= 2.0f * deltaTime;
	}

	if (m_pPlayerController->IsDownHeld() == true)
	{
		m_Pos.y -= 2.0f * deltaTime;
	}

	if (m_pPlayerController->IsRightHeld() == true)
	{
		m_Pos.x += 2.0f * deltaTime;
	}

	ImGui::DragFloat2("Position", &m_Pos.x, 0.1f);
}


