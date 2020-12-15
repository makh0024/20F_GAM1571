#pragma once
#include "GamePCH.h"

class PlayerController;
class Pathfinder;
class Tilemap;
class Bomb;

class Enemy : public fw::GameObject
{
public:
	Enemy(float x, float y, std::string Name, fw::Mesh* Mesh, fw::ShaderProgram* Shader, fw::vec4 color, fw::GameCore* pGameCore, fw::Spritesheet* pSpritesheet,
		fw::vec2 playerScale, Pathfinder* pPathfinder, Tilemap* ptileMap);
	~Enemy();

	void Update(float deltaTime);

	void FindPath();

	void PlaceBomb();

	std::vector<int> unsafetiles;
protected:
	//PlayerController* m_pPlayerController;

	Pathfinder* m_pPathfinder;

	fw::Spritesheet* m_pSpritesheet = nullptr;
private:
	fw::FWCore* m_pFramework = nullptr;

	fw::Sprite* DefaultSprite;

	Tilemap* m_pTilemap;

	float waittime;

	bool hasreached = true;

	int m_endx;
	int m_endy;

	fw::vec2 finalpos;
	fw::vec2 initialpos;
	fw::vec2 direction;

	float timer = 0.f;

	bool hasreachednexttile = true;

	bool timerstart = false;

	float AnimDelay;

	fw::vec2 m_Displacement;
	fw::vec2 m_StartingPosition;
	float m_Remaining;
	float m_Duration;

	float breaktime;

	bool m_isAlive = true;

	bool runbreaktime = false;

	int findpathtimes = 0;

	bool hasplacedbomb = false;

	float placingtimer = 0.f;
	bool hasplaced = false;

	bool isbombactive = false;
};