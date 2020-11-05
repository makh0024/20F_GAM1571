#pragma once


class PlayerController
{
public: 
	enum Mask
	{
		Up = 1,
		Down = 2,
		Left = 4,
		Right = 8,
	};

	PlayerController();
	virtual ~PlayerController();

	void StartFrame();
	void OnEvent(fw::Event* pEvent);

	bool IsUpHeld()		{ return (m_Flags & Up) != 0; }
	bool IsLeftHeld()	{ return (m_Flags & Left) != 0; }
	bool IsDownHeld()	{ return (m_Flags & Down) != 0; }
	bool IsRightHeld()	{ return (m_Flags & Right) != 0; }

	bool IsHeld(Mask mask);
	bool WasNewlyPressed(Mask mask);
	bool WasNewlyReleased(Mask mask);

protected:
	unsigned int m_Flags = 0;
	unsigned int m_OldFlags = 0;

	//bool m_Up = false;
	//bool m_Down = false;
	//bool m_Left = false;
	//bool m_Right = false;
};