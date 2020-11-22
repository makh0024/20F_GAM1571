#pragma once
#include "GamePCH.h"

class PlayerController;

class Player : public fw::GameObject
{
public:
	Player(float x, float y, std::string Name, PlayerController* pPlayerController,
		fw::Mesh* Mesh, fw::ShaderProgram* Shader, fw::vec4 color, fw::GameCore* pGameCore, fw::Spritesheet* pSpritesheet);
	~Player();

	void Update(float deltaTime);

protected:
	PlayerController* m_pPlayerController;

	fw::Spritesheet* m_pSpritesheet = nullptr;
private:
	fw::FWCore* m_pFramework = nullptr;

	fw::Sprite* DefaultSprite;

	float AnimDelay;
};