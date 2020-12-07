#include "GamePCH.h"


#include "Events/GameEvents.h"

#include "Characters/PlayerController.h"

#include "Characters/Player.h"
#include "Characters/Shapes.h"
#include "Tilemap/Tilemap.h"
#include "Tilemap/Layout.h"
#include "Pathfinder/Pathfinder.h"
#include "Characters/Enemy.h"

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

    m_pTilemap->SendPlayerPos(m_pPlayer->GetPosition());
    //m_pEnemy->ChangeCameraPos(m_pPlayer->GetPosition());
   // m_pPlayer->ChangeCameraPos(m_pPlayer->GetPosition());


    for (int i = 0; i < m_gameObjects.size(); i++)
    {
        m_gameObjects.at(i)->Update(deltaTime);

        m_gameObjects.at(i)->ChangeCameraPos(m_pPlayer->GetPosition());

        ImGui::PushID(m_gameObjects.at(i));
        
        ImGui::PopID();
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

    //Load Meshs
    m_pMeshs["Player"] = new fw::Mesh(meshPrimType_Sprite, meshNumVerts_Sprite, meshAttribs_Sprite);
    //Load Spritesheet
    m_pSpritesheet = new fw::Spritesheet("Data/Textures/Bomberman.json");

    //Create GameObjects
    m_pPlayer = new Player(5.f, 5.f, "Circle", m_pPlayerController, m_pMeshs["Player"], m_pShaders["Basic"], fw::vec4::White(1.0f), this, m_pSpritesheet, fw::vec2(0.5f, 1.f));
    m_pPlayer->SetTexture(m_pTextures["Player"]);

    //m_pPlayer2 = new Player(0.5f, 0.5f, "Circle", m_pPlayerController, m_pMeshs["Player"], m_pShaders["Basic"], fw::vec4::White(1.0f), this, m_pSpritesheet);

    m_gameObjects.push_back(m_pPlayer);
    //m_gameObjects.push_back(m_pPlayer2);

    //Settings
    wglSwapInterval(m_VSyncEnabled ? 1 : 0);

    //Tilemap Settings
    m_pTilemap = new Tilemap(10, 10, level1Layout, m_pMeshs["Player"], m_pShaders["Basic"], m_pTextures["Player"], m_pSpritesheet, m_pPlayer);

    m_pPathfinder = new Pathfinder(m_pTilemap, 10, 10);

    m_pEnemy = new Enemy(2.f, 2.f, "Circle", m_pMeshs["Player"], m_pShaders["Basic"], fw::vec4::White(1.0f), this, m_pSpritesheet, fw::vec2(0.5f, 1.f), m_pPathfinder, m_pTilemap);

    m_gameObjects.push_back(m_pEnemy);
}
