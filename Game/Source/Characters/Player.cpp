#include "GamePCH.h"

#include "Player.h"
using namespace fw;

#include "PlayerController.h"

Player::Player(float x, float y, std::string Name, PlayerController* pPlayerController, Mesh* Mesh, ShaderProgram* Shader, fw::vec4 color, GameCore* pGameCore) : fw::GameObject (x, y, Name, Mesh, Shader, color, pGameCore, Type::Player)
{
	m_pFramework = m_pGameCore->GetFramework();
	m_pPlayerController = pPlayerController;
}

Player::~Player()
{
}

void Player::Update(float deltaTime)
{
	if (m_pPlayerController->IsHeld(PlayerController::Mask::Up))
	{
		m_Pos.y += 2.0f * deltaTime;
	}

	if (m_pPlayerController->IsHeld(PlayerController::Mask::Left))
	{
		m_Pos.x -= 2.0f * deltaTime;
	}

	if (m_pPlayerController->IsHeld(PlayerController::Mask::Down))
	{
		m_Pos.y -= 2.0f * deltaTime;
	}

	if (m_pPlayerController->IsHeld(PlayerController::Mask::Right))
	{
		m_Pos.x += 2.0f * deltaTime;
	}

	ImGui::DragFloat2("Position", &m_Pos.x, 0.1f);
}


