#include "GamePCH.h"

#include "Enemy.h"
using namespace fw;

Enemy::Enemy(float x, float y, float radius, std::string Name, Mesh* Mesh, ShaderProgram* Shader, fw::vec4 color, GameCore* pGameCore) : fw::GameObject (x, y, Name, Mesh, Shader, color, pGameCore)
{
	m_pFramework = m_pGameCore->GetFramework();

	m_SpawnRadius = radius;

	float angle = rand() % 360;

	angle *= 3.1415926 / 180;

	m_Pos = fw::vec2(5, 5) + (fw::vec2(cos(angle), sin(angle)) * m_SpawnRadius);

	m_direction = fw::vec2(x - m_Pos.x, y - m_Pos.y).Normalized();

	m_speed = 1 + (float)((rand() % 40) / 10);
}

Enemy::~Enemy()
{
}

void Enemy::Update(float deltaTime)
{
	m_Pos += m_direction * m_speed * deltaTime;
}
