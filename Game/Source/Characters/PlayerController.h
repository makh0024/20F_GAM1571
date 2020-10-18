#pragma once


class PlayerController
{
public: 
	PlayerController();
	virtual ~PlayerController();

	void Update(fw::GameCore* gamecore);

	bool IsUpHeld() { return m_Up; }
	bool IsLeftHeld() { return m_Left; }
	bool IsDownHeld() { return m_Down; }
	bool IsRightHeld() { return m_Right; }

protected:
	bool m_Up = false;
	bool m_Down = false;
	bool m_Left = false;
	bool m_Right = false;
};