#pragma once

namespace fw
{
	struct Sprite
	{
	public:
		std::string m_SpriteName;
		int m_OffsetX, m_OffsetY, m_ScaleX, m_ScaleY;

		Sprite(std::string SpriteName, int OffsetX, int OffsetY, int ScaleX, int ScaleY)
		{
			m_SpriteName = SpriteName;
			m_OffsetX = OffsetX;
			m_OffsetY = OffsetY;
			m_ScaleX = ScaleX;
			m_ScaleY = ScaleY;
		}
	};

	class Spritesheet
	{
	public:
		Spritesheet(char* fileloc);
		~Spritesheet();

		Sprite* GetSpriteInfo(std::string spriteName);

	protected:
		rapidjson::Document m_doc;

		std::vector <Sprite*> m_Sprites;
	};
}