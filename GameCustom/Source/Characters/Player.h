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

	void SetBomb(Bomb* pBomb);

protected:
	PlayerController* m_pPlayerController;

	fw::Spritesheet* m_pSpritesheet = nullptr;
private:
	fw::FWCore* m_pFramework = nullptr;

	fw::Sprite* DefaultSprite;

	float AnimDelay;

	fw::vec2 m_dir;

	Bomb* m_pBomb;

	Tilemap* m_pTilemap;

	bool CanMove(float deltaTime);
};