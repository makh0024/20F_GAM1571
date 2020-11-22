#pragma once
#include "GamePCH.h"

class SmolBody : public fw::GameObject
{
public:
	SmolBody(float x, float y, float radius, std::string Name, fw::Mesh* Mesh, fw::ShaderProgram* Shader, fw::vec4 color, fw::GameCore* pGameCore);
	~SmolBody();

	void Update(float deltaTime);

protected:
	fw::vec2 m_PlayerPosition;
private:
	fw::FWCore* m_pFramework = nullptr;

	fw::vec2 m_direction;

	float m_speed;

	float m_SpawnRadius;
};