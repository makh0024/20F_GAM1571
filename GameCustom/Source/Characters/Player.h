#pragma once
#include "GamePCH.h"

class PlayerController;
class Tilemap;
class Bomb;

class Player : public fw::GameObject
{
public:
	Player(float x, float y, std::string Name, PlayerController* pPlayerController,
		fw::Mesh* Mesh, fw::ShaderProgram* Shader, fw::vec4 color, fw::GameCore* pGameCore, fw::Spritesheet* pSpritesheet, fw::vec2 playerScale, Tilemap* pTilemap);
	~Player();

	void Update(float deltaTime);

protected:
	PlayerController* m_pPlayerController;

	fw::Spritesheet* m_pSpritesheet = nullptr;
private:
	fw::FWCore* m_pFramework = nullptr;

	fw::Sprite* DefaultSprite;

	float AnimDelay;

	fw::vec2 m_dir;

	Tilemap* m_pTilemap;

	bool CanMove(float deltaTime);

	bool m_isAlive = true;

	float placingtimer = 0.f;
	bool hasplaced = false;

	//bool m_hasExploded = false;
};