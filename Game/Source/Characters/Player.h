#pragma once
#include "Framework.h"

class Player : public fw::GameObject
{
public:
	Player(float x, float y, fw::Mesh* Mesh, fw::ShaderProgram* Shader, fw::GameCore* pGameCore);
	~Player();

	void Update(float deltaTime);

protected:

private:
	fw::FWCore* m_pFramework = nullptr;
};