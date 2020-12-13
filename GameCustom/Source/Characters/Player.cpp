#include "GamePCH.h"

#include "Player.h"
using namespace fw;

#include "PlayerController.h"
#include "Tilemap/Tilemap.h"
#include "GameItems/Bomb.h"

Player::Player(float x, float y, std::string Name, PlayerController* pPlayerController, Mesh* Mesh, ShaderProgram* Shader, fw::vec4 color, GameCore* pGameCore, fw::Spritesheet* pSpritesheet, fw::vec2 playerScale, Tilemap* pTilemap) :
	fw::GameObject (x, y, Name, Mesh, Shader, color, pGameCore, Type::Player, playerScale)
{
	//m_pFramework = m_pGameCore->GetFramework();
	m_pPlayerController = pPlayerController;

	m_pSpritesheet = pSpritesheet;

	DefaultSprite = m_pSpritesheet->GetSpriteInfo("BM_WalkDown1");

	AnimDelay = 0.0f;

	m_dir = fw::vec2(0, 0);

	m_pTilemap = pTilemap;

	//m_pBombpng = new Texture("Data/Textures/Bomb.png");
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
		m_dir.y = 2.0f;
		m_dir.x = 0.f;
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
		m_dir.x = -2.0f;
		m_dir.y = 0.f;
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
		m_dir.y = -2.0f;
		m_dir.x = 0.f;
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
		m_dir.x = 2.0f;
		m_dir.y = 0.f;
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
		m_dir.x = 0;
		m_dir.y = 0;
		DefaultSprite = m_pSpritesheet->GetSpriteInfo("BM_WalkDown1");
	}

	m_UVOffset = vec2(DefaultSprite->m_OffsetX / (float)m_pSpritesheet->m_Width, DefaultSprite->m_OffsetY / (float)m_pSpritesheet->m_Height);
	m_UVScale = vec2(DefaultSprite->m_ScaleX / (float)m_pSpritesheet->m_Width, DefaultSprite->m_ScaleY / (float)m_pSpritesheet->m_Height);

	if (CanMove(deltaTime) == true)
		m_Pos += m_dir * deltaTime;

	ImGui::DragFloat2("Position", &m_Pos.x, 0.1f);

	if (m_pPlayerController->IsHeld(PlayerController::Mask::Throw) == true)
	{
		if (m_pBomb->m_isActive == false)
		{
			m_pBomb->SetPosition(fw::vec2((int)(m_Pos.x + 0.5f), (int)m_Pos.y));
			m_pBomb->SetIsActive(true);
		}
	}
}

void Player::SetBomb(Bomb* pBomb)
{
	m_pBomb = pBomb;
}

bool Player::CanMove(float deltaTime)
{
	vec2 point1 = m_Pos + m_dir * 2.f * deltaTime + vec2(0.3f, 0.0f);
	bool canwalkp1 = m_pTilemap->IsTileWalkableAtTilePos((int)point1.x, (int)point1.y);
	
	vec2 point2 = m_Pos + m_dir * 2.f * deltaTime + vec2(0.3f, 0.3f);
	bool canwalkp2 = m_pTilemap->IsTileWalkableAtTilePos((int)point2.x, (int)point2.y);
	
	vec2 point3 = m_Pos + m_dir * 2.f * deltaTime + vec2(0.65f, 0.3f);
	bool canwalkp3 = m_pTilemap->IsTileWalkableAtTilePos((int)point3.x, (int)point3.y);
	
	vec2 point4 = m_Pos + m_dir * 2.f * deltaTime + vec2(0.65f, 0.0f);
	bool canwalkp4 = m_pTilemap->IsTileWalkableAtTilePos((int)point4.x, (int)point4.y);

	if (canwalkp1 == true && canwalkp2 == true && canwalkp3 == true && canwalkp4 == true)
		return true;
	else
		return false;
}


