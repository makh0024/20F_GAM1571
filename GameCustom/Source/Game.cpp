#include "GamePCH.h"


#include "Events/GameEvents.h"

#include "Characters/PlayerController.h"

#include "Characters/Player.h"
#include "Characters/Shapes.h"
#include "Tilemap/Tilemap.h"
//#include "Tilemap/DestructibleTilemap.h"
#include "Tilemap/Layout.h"
#include "Pathfinder/Pathfinder.h"
#include "Characters/Enemy.h"
#include "GameItems/Bomb.h"

#include "Game.h"

Game::Game(fw::FWCore* pFramework) : fw::GameCore(pFramework)
{
    m_pFramework = pFramework;
    m_boundaryRad = 3.0f;
    m_numSides = 50;
}

Game::~Game()
{
    delete m_pEventManager;
    delete m_pImguiMan; 
    delete m_pPlayerController;

    delete m_pSpritesheet;

    delete m_pTilemap;

    delete m_pPathfinder;

    for (fw::GameObject* pObject : m_gameObjects)
    {
        delete pObject;
    }

    for (fw::GameObject* pObject : m_pBombs)
    {
        delete pObject;
    }

    for ( std::pair<std::string, fw::ShaderProgram*> object : m_pShaders)
    {
        delete object.second;
    }

    for (std::pair<std::string, fw::Mesh*> object : m_pMeshs)
    {
        delete object.second;
    }

    for (std::pair<std::string, fw::Texture*> object : m_pTextures)
    {
        delete object.second;
    }
}

void Game::Update(float deltaTime)
{
    
    float x = 1.0f / deltaTime;

    m_pEventManager->DispatchAllEvents(deltaTime, this);

    m_pImguiMan->StartFrame(deltaTime);
    ImGui::ShowDemoWindow();

    if (m_pPlayer != nullptr)
    {
        m_pTilemap->SendPlayerPos(m_pPlayer->GetPosition());
    }

    for (int i = 0; i < m_gameObjects.size(); i++)
    {
        m_gameObjects.at(i)->Update(deltaTime);

        if (m_pPlayer != nullptr)
            m_gameObjects.at(i)->ChangeCameraPos(m_pPlayer->GetPosition());
    }

    for (int i = 0; i < m_pBombs.size(); i++)
    {
        m_pBombs.at(i)->Update(deltaTime);
        
        for (int u = 0; u < 9; u++)
        {
            if (m_pEnemy != nullptr)
            {
                m_pEnemy->unsafetiles.push_back(m_pBombs.at(i)->explodedtiles[u]);
            }
        }

        //m_pBombs.at(i)->ChangeCameraPos(m_pPlayer->GetPosition());
    }

    if (ImGui::Checkbox("VSync", &m_VSyncEnabled))
    {
        wglSwapInterval(m_VSyncEnabled ? 1 : 0);
    }

}

void Game::Draw()
{
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    m_pTilemap->Draw();
   
    for (int i = 0; i < m_pBombs.size(); i++)
    {
        m_pBombs.at(i)->Draw();
    }
   
    for (int i = 0; i < m_gameObjects.size(); i++)
    {
        m_gameObjects.at(i)->Draw();
    }


    m_pImguiMan->EndFrame();
}

void Game::OnEvent(fw::Event* pEvent)
{
    m_pPlayerController->OnEvent(pEvent);

    if (pEvent->GetType() == RemoveFromGameEvent::GetStaticEventType())
    {
        RemoveFromGameEvent* pRemoveFromGameEvent = static_cast<RemoveFromGameEvent*>(pEvent);
        fw::GameObject* pObject = pRemoveFromGameEvent->GetGameObject();

        auto it = std::find(m_gameObjects.begin(), m_gameObjects.end(), pObject);
        m_gameObjects.erase(it);

        delete pObject;
    }  

    if (pEvent->GetType() == BombExplosionEvent::GetStaticEventType())
    {
        BombExplosionEvent* pbombmadeby = static_cast<BombExplosionEvent*>(pEvent);
        fw::GameObject* pObject = pbombmadeby->GetGameObject();

        Bomb* tempBomb = new Bomb(6.f, 8.f, "Bomb", m_pMeshs["Player"], m_pShaders["Basic"], fw::vec4::White(1.f), this, fw::vec2(0.5f, 0.5f), m_pTilemap);
        tempBomb->SetTexture(m_pTextures["Bomb"]);

        if (tempBomb->m_isActive == false)
        {
            tempBomb->SetPosition(fw::vec2((float)((int)(pObject->GetPosition().x + 0.5f)), (float)((int)(pObject->GetPosition().y))));
            tempBomb->SetIsActive(true);
        }

        /*for (int i = 0; i < 9; i++)
        {
            m_pEnemy->unsafetiles.push_back(tempBomb->explodedtiles[i]);
        }*/

        m_pBombs.push_back(tempBomb);
        //m_gameObjects.push_back(tempBomb);
    }

    if (pEvent->GetType() == RemoveBombFromGameEvent::GetStaticEventType())
    {
        RemoveBombFromGameEvent* pRemoveBombFromGameEvent = static_cast<RemoveBombFromGameEvent*>(pEvent);
        Bomb* pObject = pRemoveBombFromGameEvent->GetBomb();
        
        //also updates unsafetiles to enemy
        if (m_pEnemy != nullptr)
        {
            if (m_pEnemy->unsafetiles.size() > 0)
            {
                for (int i = 0; i < m_pEnemy->unsafetiles.size(); i++)
                {
                    for (int u = 0; u < 9; u++)
                    {
                        if (i < m_pEnemy->unsafetiles.size())
                        {
                            if (m_pEnemy->unsafetiles.at(i) == pObject->explodedtiles[u])
                            {
                                m_pEnemy->unsafetiles.erase(m_pEnemy->unsafetiles.begin() + i);
                            }
                        }
                    }
                }
            }
        }

        //this function also checks for enemy and player deaths
        if (m_pEnemy != nullptr)
        {
            fw::vec2 enemyPos = m_pEnemy->GetPosition();
            int enemytile = (int)(enemyPos.y) * (int)(m_pTilemap->m_MapSize.x) + (int)(enemyPos.x + 0.5f);
            for (int i = 0; i < pObject->actuallyexploded.size(); i++)
            {
                if (enemytile == pObject->actuallyexploded[i])
                {
                    m_pEventManager->AddEvent(new RemoveFromGameEvent(m_pEnemy), 0.f);
                    m_pEnemy = nullptr;
                }
            }
        }

        if (m_pPlayer != nullptr)
        {
            fw::vec2 playerPos = m_pPlayer->GetPosition();

            int playertile = (int)(playerPos.y) * (int)(m_pTilemap->m_MapSize.x) + (int)(playerPos.x + 0.5f);

            for (int i = 0; i < pObject->actuallyexploded.size(); i++)
            {
                if (playertile == pObject->actuallyexploded[i])
                {
                    m_pEventManager->AddEvent(new RemoveFromGameEvent(m_pPlayer), 0.f);
                    m_pPlayer = nullptr;
                }
            }
        }
        auto it = std::find(m_pBombs.begin(), m_pBombs.end(), pObject);
        m_pBombs.erase(it);

        delete pObject;
    }
}

void Game::StartFrame(float deltaTime)
{    
    m_pPlayerController->StartFrame();

    m_pEventManager->DispatchAllEvents(deltaTime, this);
}

void Game::Init()
{
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    m_pEventManager = new fw::EventManager();

    m_pImguiMan = new fw::ImGuiManager(m_pFramework);
    m_pImguiMan->Init();
    
    m_pPlayerController = new PlayerController();
    
    //Load Shaders
    m_pShaders["Basic"] = new fw::ShaderProgram("Data/Basic.vert", "Data/Basic.frag");

    //Load Textures
    m_pTextures["Player"] = new fw::Texture("Data/Textures/Bomberman.png");
    m_pTextures["Bomb"] = new fw::Texture("Data/Textures/Bomb.png");

    //Load Meshs
    m_pMeshs["Player"] = new fw::Mesh(meshPrimType_Sprite, meshNumVerts_Sprite, meshAttribs_Sprite);

    //Load Spritesheet
    m_pSpritesheet = new fw::Spritesheet("Data/Textures/Bomberman.json");

    //Create GameObjects
    //Settings
    wglSwapInterval(m_VSyncEnabled ? 1 : 0);

    //Tilemap Settings
    m_pTilemap = new Tilemap(10, 10, level1Layout, m_pMeshs["Player"], m_pShaders["Basic"], m_pTextures["Player"], m_pSpritesheet);

    m_pPlayer = new Player(8.f, 8.f, "Circle", m_pPlayerController, m_pMeshs["Player"], m_pShaders["Basic"], fw::vec4::White(1.0f), this, m_pSpritesheet, fw::vec2(0.5f, 1.f), m_pTilemap);
    m_pPlayer->SetTexture(m_pTextures["Player"]);
    m_gameObjects.push_back(m_pPlayer);
    

    m_pPathfinder = new Pathfinder(m_pTilemap, 10, 10);
    m_pEnemy = new Enemy(1.f, 1.f, "Circle", m_pMeshs["Player"], m_pShaders["Basic"], fw::vec4::White(1.0f), this, m_pSpritesheet, fw::vec2(0.5f, 1.f), m_pPathfinder, m_pTilemap);
    m_pEnemy->SetTexture(m_pTextures["Player"]);
    m_gameObjects.push_back(m_pEnemy);
}
