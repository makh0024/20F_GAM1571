#include "GamePCH.h"
#include "PlayerController.h"

PlayerController::PlayerController()
{
}

PlayerController::~PlayerController()
{
}

void PlayerController::StartFrame()
{
	m_OldFlags = m_Flags;
}

void PlayerController::OnEvent(fw::Event* pEvent)
{
	if (pEvent->GetType() == fw::InputEvent::GetStaticEventType())
	{
		fw::InputEvent* pInputEvent = static_cast<fw::InputEvent*>(pEvent);

		if (pInputEvent->GetDeviceType() == fw::InputEvent::DeviceType::Keyboard
			&& pInputEvent->GetDeviceState() == fw::InputEvent::DeviceState::Pressed)
		{
			if (pInputEvent->GetKeyCode() == 'W') { m_Flags = m_Flags | Mask::Up; }
			if (pInputEvent->GetKeyCode() == 'A') { m_Flags = m_Flags | Mask::Left; }
			if (pInputEvent->GetKeyCode() == 'S') { m_Flags = m_Flags | Mask::Down; }
			if (pInputEvent->GetKeyCode() == 'D') { m_Flags = m_Flags | Mask::Right; }
			if (pInputEvent->GetKeyCode() == 'R') { m_Flags = m_Flags | Mask::Restart; }
			if (pInputEvent->GetKeyCode() == 'E') { m_Flags = m_Flags | Mask::Throw; }
		}

		if (pInputEvent->GetDeviceType() == fw::InputEvent::DeviceType::Keyboard
			&& pInputEvent->GetDeviceState() == fw::InputEvent::DeviceState::Released)
		{
			if (pInputEvent->GetKeyCode() == 'W') { m_Flags &= ~Mask::Up; }
			if (pInputEvent->GetKeyCode() == 'A') { m_Flags &= ~Mask::Left; }
			if (pInputEvent->GetKeyCode() == 'S') { m_Flags &= ~Mask::Down; }
			if (pInputEvent->GetKeyCode() == 'D') { m_Flags &= ~Mask::Right; }
			if (pInputEvent->GetKeyCode() == 'R') { m_Flags &= ~Mask::Restart; }
			if (pInputEvent->GetKeyCode() == 'E') { m_Flags &= ~Mask::Throw; }
		}

		/*fw::FWCore* m_pFramework = gamecore->GetFramework();

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
		}*/

		//if (pInputEvent->GetKeyCode() == 'R')
	}
}

bool PlayerController::IsHeld(Mask mask)
{
	return (m_Flags & mask) != 0;
}

bool PlayerController::WasNewlyPressed(Mask mask)
{
	return (((m_Flags & mask) !=0) && ((m_OldFlags & mask) == 0));
}

bool PlayerController::WasNewlyReleased(Mask mask)
{
	return (((m_Flags & mask) == 0) && ((m_OldFlags & mask) != 0));
}
