#include "GamePCH.h"

#include "Player.h"
using namespace fw;

#include "PlayerController.h"

Player::Player(float x, float y, std::string Name, PlayerController* pPlayerController, Mesh* Mesh, ShaderProgram* Shader, fw::vec4 color, GameCore* pGameCore, fw::Spritesheet* pSpritesheet) :
	fw::GameObject (x, y, Name, Mesh, Shader, color, pGameCore, Type::Player)
{
	m_pFramework = m_pGameCore->GetFramework();
	m_pPlayerController = pPlayerController;

	m_pSpritesheet = pSpritesheet;

	DefaultSprite = m_pSpritesheet->GetSpriteInfo("BM_WalkDown1");

	AnimDelay = 0.0f;
}

Player::~Player()
{
}

void Player::Update(float deltaTime)
{
	//ImGui::Text("pos: %f, %f", m_Pos.x, m_Pos.y);

	AnimDelay += deltaTime;

	if (AnimDelay > 0.5)
	{
		AnimDelay = 0.0f;
	}

	if (m_pPlayerController->IsHeld(PlayerController::Mask::Up))
	{
		m_Pos.y += 1.0f * deltaTime;

		int noOfFrames = 3;

		for (int i = 0; i < noOfFrames; i++)
		{
			if (AnimDelay < (0.5 / (float)noOfFrames) * i + 1 && AnimDelay > (0.5 / (float)noOfFrames) * i)
			{
				DefaultSprite =  m_pSpritesheet->GetSpriteInfo("BM_WalkUp" + std::to_string(i + 1));
			}
		}
	}

	else if (m_pPlayerController->IsHeld(PlayerController::Mask::Left))
	{
		m_Pos.x -= 1.0f * deltaTime;

		int noOfFrames = 3;

		for (int i = 0; i < noOfFrames; i++)
		{
			if (AnimDelay < (0.5 / (float)noOfFrames) * i + 1 && AnimDelay >(0.5 / (float)noOfFrames) * i)
			{
				DefaultSprite = m_pSpritesheet->GetSpriteInfo("BM_WalkLeft" + std::to_string(i + 1));
			}
		}
	}

	else if (m_pPlayerController->IsHeld(PlayerController::Mask::Down))
	{
		m_Pos.y -= 1.0f * deltaTime;

		int noOfFrames = 3;

		for (int i = 0; i < noOfFrames; i++)
		{
			if (AnimDelay < (0.5 / (float)noOfFrames) * i + 1 && AnimDelay >(0.5 / (float)noOfFrames) * i)
			{
				DefaultSprite = m_pSpritesheet->GetSpriteInfo("BM_WalkDown" + std::to_string(i + 1));
			}
		}
	}

	else if (m_pPlayerController->IsHeld(PlayerController::Mask::Right))
	{
		m_Pos.x += 1.0f * deltaTime;

		int noOfFrames = 3;

		for (int i = 0; i < noOfFrames; i++)
		{
			if (AnimDelay < (0.5 / (float)noOfFrames) * i + 1 && AnimDelay >(0.5 / (float)noOfFrames) * i)
			{
				DefaultSprite = m_pSpritesheet->GetSpriteInfo("BM_WalkRight" + std::to_string(i + 1));
			}
		}
	}

	if (m_pPlayerController->IsHeld(PlayerController::Mask::Up) == false &&
		m_pPlayerController->IsHeld(PlayerController::Mask::Down) == false &&
		m_pPlayerController->IsHeld(PlayerController::Mask::Left) == false &&
		m_pPlayerController->IsHeld(PlayerController::Mask::Right) == false)
	{
		DefaultSprite = m_pSpritesheet->GetSpriteInfo("BM_WalkDown1");
	}

	m_UVOffset = vec2(DefaultSprite->m_OffsetX / 256.0f, DefaultSprite->m_OffsetY / 128.0f);
	m_UVScale = vec2(DefaultSprite->m_ScaleX / 256.0f, DefaultSprite->m_ScaleY / 128.0f);

	ImGui::DragFloat2("Position", &m_Pos.x, 0.1f);
}


