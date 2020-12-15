#include "GamePCH.h"

#include "Pathfinder/Pathfinder.h"
#include "Enemy.h"
#include "Tilemap/Tilemap.h"
#include "GameItems/Bomb.h"

#include "Events/GameEvents.h"

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


	waittime = 0;

	breaktime = 0;
	
	FindPath();
}

Enemy::~Enemy()
{
}

void Enemy::Update(float deltaTime)
{
	if (m_isAlive == true)
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
			if (breaktime == 0.f && ((findpathtimes % 2 == 0) || isbombactive == false))
			{
				FindPath();
			}
			if (findpathtimes % 2 == 1 && hasplacedbomb == false && isbombactive == false)
				findpathtimes++;
		}

		if (runbreaktime == true)
		{
			breaktime += deltaTime;

			if (hasplaced == true)
			{
				if (breaktime > 0.4f)
				{
					hasreached = true;
					findpathtimes++;
					runbreaktime = false;

					breaktime = 0.f;
				}
			}
			else
			{
				if (breaktime > 1)
				{
					hasreached = true;
					findpathtimes++;
					runbreaktime = false;

					breaktime = 0.f;
				}
			}
		}

		if (m_Displacement.x == 0 && m_Displacement.y == 0)
		{
			if (hasplaced == false)
			{
				findpathtimes++;

				PlaceBomb();
			}
			else
				hasplacedbomb = false;

		}

		//if (m_pBomb->timer > 3.99f || m_pOtherBomb->timer > 3.99f)
		//{
		//	int playertile = (int)(m_Pos.y) * m_pTilemap->m_MapSize.x + (int)(m_Pos.x + 0.5f);
		//
		//	for (int i = 0; i < 9; i++)
		//	{
		//		if (m_pBomb->m_isActive == true)
		//		{
		//			if (playertile == m_pBomb->explodedtiles[i])
		//			{
		//				SetCanDraw(false);
		//
		//				m_isAlive = false;
		//			}
		//		}
		//		else if (m_pOtherBomb->m_isActive == true)
		//		{
		//			if (playertile == m_pOtherBomb->explodedtiles[i])
		//			{
		//				SetCanDraw(false);
		//
		//				m_isAlive = false;
		//			}
		//		}
		//	}
		//}

		if (hasplaced == true)
		{
			placingtimer += deltaTime;
			isbombactive = true;

			if (placingtimer > 4)
			{
				hasplaced = false;
				placingtimer = 0.f;
			}
		}
	}
	//ImGui::Text("finalpos: %f, %f", finalpos.x, finalpos.y);
}

void Enemy::FindPath()
{
	int startx = (int)m_pTilemap->CurrentTileAt(fw::vec2(m_Pos.x, m_Pos.y)).x;
	int starty = (int)m_pTilemap->CurrentTileAt(fw::vec2(m_Pos.x, m_Pos.y)).y;

	std::vector<int> safetiles;

	if (hasreached == true)
	{
		//m_endx = (rand() % (int)m_pTilemap->m_MapSize.x + 1) - 1;
		//m_endy = (rand() % (int)m_pTilemap->m_MapSize.y + 1) - 1;


		for (int i = 0; i < 100; i++)
		{
			if (m_pTilemap->m_pLayout[i] == Tilemap::TileType::Floor)
			{
				safetiles.push_back(i);

				for (int u = 0; u < unsafetiles.size(); u++)
				{
					if (safetiles.back() == unsafetiles[u])
					{
						safetiles.erase(safetiles.begin() + safetiles.size() - 1);
						break;
					}
				}
			}
		}

		std::vector<int> possibleEndx;
		std::vector<int> possibleEndy;

		for (int i = 0; i < safetiles.size(); i++)
		{
			int safetilex = safetiles[i] % ((int)m_pTilemap->m_MapSize.x);
			int safetiley = safetiles[i] / ((int)m_pTilemap->m_MapSize.y);

			bool found = m_pPathfinder->FindPath(startx, starty, safetilex, safetiley);
						
			if (found == true && (safetilex != startx || safetiley != starty))
			{
				possibleEndx.push_back(safetilex);

				possibleEndy.push_back(safetiley);

				//break;
			}
			
		}
		if (possibleEndx.size() > 0)
		{
			int randomnum = rand() % possibleEndx.size();
			m_endx = possibleEndx[randomnum];
			m_endy = possibleEndy[randomnum];
		}
		else
		{
			m_endx = 1;
			m_endy = 1;
		}
		hasreached = false;
	}

	bool found = m_pPathfinder->FindPath(startx, starty, m_endx, m_endy);
	//OutputMessage("Found = %d\n", found);
		
	int path[255];
	int len = m_pPathfinder->GetPath(path, 255, m_endx, m_endy);

	for (int u = 0; u < len - 1; u++)
	{
		for (int i = 0; i < safetiles.size(); i++)
		{
			if (path[u] != safetiles[i])
			{
				len = m_pPathfinder->GetPath(path, 255, m_endx, m_endy);
				
			}
		}
	}

	if (len > 1)
	{
		int nexttilex;
		int nexttiley;

		nexttilex = path[len - 2] % ((int)m_pTilemap->m_MapSize.x);
		nexttiley = path[len - 2] / ((int)m_pTilemap->m_MapSize.y);
		
		/*for (int i = 0; i < safetiles.size(); i++)
		{
			if (path[len - 2] == safetiles[i])
			{
				nexttilex = path[len - 2] % ((int)m_pTilemap->m_MapSize.x);
				nexttiley = path[len - 2] / ((int)m_pTilemap->m_MapSize.y);
				break;
			}
		}*/

		int nexttile = path[len - 2];
		
		if (m_pTilemap->IsTileWalkableAtTilePos(nexttilex, nexttiley) == true)
		{
			fw::vec2 position = fw::vec2((float)nexttilex, (float)nexttiley);
			float distance = position.Distance(m_Pos);

			m_Duration = distance / 2.f;
			m_Remaining = m_Duration;

			m_Displacement = position - m_Pos;

			m_StartingPosition = m_Pos;
		}
		
		
	}
	else
	{
		m_Displacement = fw::vec2(0.f, 0.f);

		runbreaktime = true;
	}

	/*OutputMessage("Length = %d\n", len);
	for (int i = 0; i < len; i++)
	{
		OutputMessage("%d\n", path[i]);
	}

	OutputMessage("done\n");*/
	
	
}

void Enemy::PlaceBomb()
{
	if (hasplaced == false)
	{
		m_pGameCore->GetEventManager()->AddEvent(new BombExplosionEvent(this), 0.f);

		hasplacedbomb = true;
		hasplaced = true;
		isbombactive = true;
		/*m_pBomb->SetPosition(fw::vec2((int)(m_Pos.x + 0.5f), (int)m_Pos.y));
		m_pBomb->SetIsActive(true);*/
	}
}