#include "GamePCH.h"
#include "PlayerController.h"

PlayerController::PlayerController()
{
}

PlayerController::~PlayerController()
{
}

void PlayerController::Update(fw::GameCore* gamecore)
{
	fw::FWCore* m_pFramework = gamecore->GetFramework();

	m_Up = false;
	m_Down = false;
	m_Left = false;
	m_Right = false;

	if (m_pFramework->IsKeyDown('W') || m_pFramework->IsKeyDown(VK_UP))
	{
		m_Up = true;
	}

	if (m_pFramework->IsKeyDown('A') || m_pFramework->IsKeyDown(VK_LEFT))
	{
		m_Left = true;
	}

	if (m_pFramework->IsKeyDown('S') || m_pFramework->IsKeyDown(VK_DOWN))
	{
		m_Down = true;
	}

	if (m_pFramework->IsKeyDown('D') || m_pFramework->IsKeyDown(VK_RIGHT))
	{
		m_Right = true;
	}
}
