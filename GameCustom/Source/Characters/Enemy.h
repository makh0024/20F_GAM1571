#pragma once
#include "GamePCH.h"

class Enemy : public fw::GameObject
{
public:
	Enemy(float x, float y, float radius, std::string Name, fw::Mesh* Mesh, fw::ShaderProgram* Shader, fw::vec4 color, fw::GameCore* pGameCore);
	~Enemy();

	void Update(float deltaTime);

protected:
	fw::vec2 m_PlayerPosition;
private:
	fw::FWCore* m_pFramework = nullptr;

	fw::vec2 m_direction;

	float m_speed;

	float m_SpawnRadius;
};