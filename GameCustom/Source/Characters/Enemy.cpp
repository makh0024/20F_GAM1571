#include "GamePCH.h"

#include "Pathfinder/Pathfinder.h"
#include "Enemy.h"
#include "Tilemap/Tilemap.h"

using namespace fw;

#include "PlayerController.h"

Enemy::Enemy(float x, float y, std::string Name, Mesh* Mesh, ShaderProgram* Shader, fw::vec4 color, GameCore* pGameCore, fw::Spritesheet* pSpritesheet, fw::vec2 playerScale, Pathfinder* pPathfinder, Tilemap* ptileMap) :
	fw::GameObject (x, y, Name, Mesh, Shader, color, pGameCore, Type::Enemy, playerScale)
{
	m_pFramework = m_pGameCore->GetFramework();
	//m_pPlayerController = pPlayerController;

	m_pSpritesheet = pSpritesheet; 

	DefaultSprite = m_pSpritesheet->GetSpriteInfo("BM_WalkDown1");

	AnimDelay = 0.0f;

	m_pPathfinder = pPathfinder;

	//ChangeCameraPos(playerPos);

	m_pTilemap = ptileMap;

	FindPath();

	waittime = 0;

	breaktime = 0;
}

Enemy::~Enemy()
{
}

void Enemy::Update(float deltaTime)
{
	ImGui::DragFloat2("enemyPosition", &m_Pos.x, 0.1f);

	m_UVOffset = vec2(DefaultSprite->m_OffsetX / (float)m_pSpritesheet->m_Width, DefaultSprite->m_OffsetY / (float)m_pSpritesheet->m_Height);
	m_UVScale = vec2(DefaultSprite->m_ScaleX / (float)m_pSpritesheet->m_Width, DefaultSprite->m_ScaleY / (float)m_pSpritesheet->m_Height);

	AnimDelay += deltaTime;

	if (AnimDelay > 0.5)
	{
		AnimDelay = 0.0f;
	}

	if (m_Displacement.y > 0)
	{
		//m_Pos.y += 2.0f * deltaTime;

		int noOfFrames = 3;

		for (int i = 0; i < noOfFrames; i++)
		{
			if (AnimDelay < (0.5 / (float)noOfFrames) * i + 1 && AnimDelay >(0.5 / (float)noOfFrames) * i)
			{
				DefaultSprite = m_pSpritesheet->GetSpriteInfo("BM_WalkUp" + std::to_string(i + 1));
			}
		}
	}

	else if (m_Displacement.x < 0)
	{
		//m_Pos.x -= 2.0f * deltaTime;

		int noOfFrames = 3;

		for (int i = 0; i < noOfFrames; i++)
		{
			if (AnimDelay < (0.5 / (float)noOfFrames) * i + 1 && AnimDelay >(0.5 / (float)noOfFrames) * i)
			{
				DefaultSprite = m_pSpritesheet->GetSpriteInfo("BM_WalkLeft" + std::to_string(i + 1));
			}
		}
	}

	else if (m_Displacement.y < 0)
	{
		//m_Pos.y -= 2.0f * deltaTime;

		int noOfFrames = 3;

		for (int i = 0; i < noOfFrames; i++)
		{
			if (AnimDelay < (0.5 / (float)noOfFrames) * i + 1 && AnimDelay >(0.5 / (float)noOfFrames) * i)
			{
				DefaultSprite = m_pSpritesheet->GetSpriteInfo("BM_WalkDown" + std::to_string(i + 1));
			}
		}
	}

	else if (m_Displacement.x > 0)
	{
		//m_Pos.x += 2.0f * deltaTime;

		int noOfFrames = 3;

		for (int i = 0; i < noOfFrames; i++)
		{
			if (AnimDelay < (0.5 / (float)noOfFrames) * i + 1 && AnimDelay >(0.5 / (float)noOfFrames) * i)
			{
				DefaultSprite = m_pSpritesheet->GetSpriteInfo("BM_WalkRight" + std::to_string(i + 1));
			}
		}
	}
	else	
	{
		DefaultSprite = m_pSpritesheet->GetSpriteInfo("BM_WalkDown1");
	}

	if (m_Remaining > 0.f)
	{
		m_Remaining -= deltaTime;
		if (m_Remaining < 0.f)
		{
			m_Remaining = 0.f;
			//FindPath();
		}

		//Calculate the percentage of the time complete 
		//(will be a value between 0.0 and 1.0)
		float percentage = 1.0f - (m_Remaining / m_Duration);

		//Calculate the position of the circle based on the 
		//percentage complete
		fw::vec2 position = m_StartingPosition + m_Displacement * percentage;
		m_Pos = position;


	}
	else
	{
		if (breaktime == 0.f)
			FindPath();
	}

	if (runbreaktime == true)
	{
		breaktime += deltaTime;

		if (breaktime > 1)
		{
			hasreached = true;
			runbreaktime = false;

			breaktime = 0.f;
		}
	}

	//ImGui::Text("finalpos: %f, %f", finalpos.x, finalpos.y);
}

void Enemy::FindPath()
{
	int startx = (int)m_pTilemap->CurrentTileAt(fw::vec2(m_Pos.x, m_Pos.y)).x;
	int starty = (int)m_pTilemap->CurrentTileAt(fw::vec2(m_Pos.x, m_Pos.y)).y;

	if (hasreached == true)
	{
		m_endx = (rand() % (int)m_pTilemap->m_MapSize.x + 1) - 1;
		m_endy = (rand() % (int)m_pTilemap->m_MapSize.y + 1) - 1;

		hasreached = false;
	}
	
	bool found = m_pPathfinder->FindPath(startx, starty, m_endx, m_endy);
	OutputMessage("Found = %d\n", found);

	int path[255];
	int len = m_pPathfinder->GetPath(path, 255, m_endx, m_endy);

	if (len > 1)
	{
			int nexttilex = path[len - 2] % ((int)m_pTilemap->m_MapSize.x);
			int nexttiley = path[len - 2] / ((int)m_pTilemap->m_MapSize.y);

			if (m_pTilemap->IsTileWalkableAtTilePos(nexttilex, nexttiley) == true)
			{
				fw::vec2 position = fw::vec2((float)nexttilex, (float)nexttiley);
				float distance = position.Distance(m_Pos);

				//Calculate the duration of the animation
				m_Duration = distance / 2.f;
				m_Remaining = m_Duration;

				//Calculate the displacement between the two points
				m_Displacement = position - m_Pos;

				//Keep track of the initial position
				m_StartingPosition = m_Pos;
			}
	}
	else
	{
		m_Displacement = fw::vec2(0.f, 0.f);		

		runbreaktime = true;
	}

	OutputMessage("Length = %d\n", len);
	for (int i = 0; i < len; i++)
	{
		OutputMessage("%d\n", path[i]);
	}

	OutputMessage("done\n");

	
}


