#pragma once
#include "GamePCH.h"

class PlayerController;

class Player : public fw::GameObject
{
public:
	Player(float x, float y, std::string Name, PlayerController* pPlayerController,
		fw::Mesh* Mesh, fw::ShaderProgram* Shader, fw::vec4 color, fw::GameCore* pGameCore);
	~Player();

	void Update(float deltaTime);

	
	

protected:
	PlayerController* m_pPlayerController;
private:
	fw::FWCore* m_pFramework = nullptr;
};