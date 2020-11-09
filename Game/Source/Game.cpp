#include "GamePCH.h"

#include "Game.h"

#include "Events/GameEvents.h"

#include "Characters/PlayerController.h"

#include "Characters/Player.h"
#include "Characters/Shapes.h"
#include "Characters/Enemy.h"
#include "Characters/HealthPickup.h"
#include "Characters/SmolBody.h"

Game::Game(fw::FWCore* pFramework) : fw::GameCore(pFramework)
{
    m_pFramework = pFramework;
    m_boundaryRad = 3.0f;
    m_numSides = 50;
    m_SpawnEnemyTimer = 0.0f;
    m_SpawnHPTimer = 0.0f;
    m_LevelTimer = 0.0f;
    m_CurrentLevel = 1;

    m_PlayerHealth = 100;

    m_PlayerState = PlayerState::Alive;

    m_SmolBodyTimer = 0.0f;
    m_IsSmolBodyTimerRunning = false;
    m_CurrentBodyRadius = 0.25f;
}

Game::~Game()
{
    delete m_pHumanMesh;
    delete m_pAnimalMesh;
    delete m_pShader;

    delete m_pEventManager;
    delete m_pImguiMan; 

    delete m_pBoundaryMesh;
    delete m_pCircleMesh;
    delete m_pEnemyMesh;
    delete m_pPickupMesh;
    delete m_pPlayerController;

    for (fw::GameObject* pObject : m_gameObjects)
    {
        delete pObject;
    }
}

void Game::Update(float deltaTime)
{
    
    float x = 1.0f / deltaTime;

    m_pEventManager->DispatchAllEvents(this);

    m_pImguiMan->StartFrame(deltaTime);
    ImGui::ShowDemoWindow();

     if (m_PlayerState != PlayerState::Dead)
     {
        for (int i = 0; i < m_gameObjects.size(); i++)
        {
            m_gameObjects.at(i)->Update(deltaTime);

            ImGui::PushID(m_gameObjects.at(i));
            //ImGui::Text("Name: %s", m_gameObjects.at(i)->GetName().c_str());
            //ImGui::SameLine();
            /*if (ImGui::Button("Delete"))
            {
                m_pEventManager->AddEvent(new RemoveFromGameEvent((m_gameObjects.at(i))));
            }*/

            if ((m_pPlayer->GetPosition() - fw::vec2(5, 5)).Magnitude() > m_boundaryRad - 0.25f)
            {
                fw::vec2 newpos = m_pPlayer->GetPosition() - fw::vec2(5, 5);
                m_pPlayer->SetPosition((newpos).Normalized() * (m_boundaryRad - 0.25f) + fw::vec2(5, 5));
            }

            if ((m_gameObjects.at(i)->GetPosition() - fw::vec2(5, 5)).Magnitude() > m_boundaryRad)
            {
                m_pEventManager->AddEvent(new RemoveFromGameEvent(m_gameObjects.at(i)));
            }

            if ((m_gameObjects.at(i)->GetType() == fw::GameObject::Type::Enemy))
            {
                if ((m_pPlayer->GetPosition() - m_gameObjects.at(i)->GetPosition()).Magnitude() <= m_CurrentBodyRadius + 0.15)
                {
                    
                    m_pEventManager->AddEvent(new RemoveFromGameEvent((m_gameObjects.at(i))));
                    m_PlayerHealth -= 10;

                    m_pCircleMesh->CreateCircle(fw::vec2(0, 0), m_CurrentBodyRadius, (m_PlayerHealth / 10) + 2 , 0.0f, true);

                    m_pPlayer->SetColor(fw::vec4::LightOrange((float)m_PlayerHealth / 100));
                }
            }
            if ((m_gameObjects.at(i)->GetType() == fw::GameObject::Type::HealthPickup))
            {
                if ((m_pPlayer->GetPosition() - m_gameObjects.at(i)->GetPosition()).Magnitude() <= m_CurrentBodyRadius + 0.15)
                {
                    m_pEventManager->AddEvent(new RemoveFromGameEvent((m_gameObjects.at(i))));
                    m_PlayerHealth += 20;

                    if (m_PlayerHealth > 100)
                        m_PlayerHealth = 100;

                    m_pCircleMesh->CreateCircle(fw::vec2(0, 0), m_CurrentBodyRadius, (m_PlayerHealth / 10) + 2, 0.0f, true);
                    m_pPlayer->SetColor(fw::vec4::LightOrange((float)m_PlayerHealth / 100));
                }
            }
            if ((m_gameObjects.at(i)->GetType() == fw::GameObject::Type::SmolBody))
            {
                if ((m_pPlayer->GetPosition() - m_gameObjects.at(i)->GetPosition()).Magnitude() <= m_CurrentBodyRadius + 0.15)
                {
                    m_pEventManager->AddEvent(new RemoveFromGameEvent((m_gameObjects.at(i))));
                    m_CurrentBodyRadius = 0.15f;
                    m_pCircleMesh->CreateCircle(fw::vec2(0, 0), m_CurrentBodyRadius, (m_PlayerHealth / 10) + 2, 0.0f, true);
                    m_IsSmolBodyTimerRunning = true;
                }
            }
            ImGui::PopID();
        }

         /*if (ImGui::SliderFloat("Radius", &m_boundaryRad, 0.0f, 5.0f, "%f"))
         {
             m_pBoundaryMesh->CreateCircle(fw::vec2(0, 0), m_boundaryRad, m_numSides, 0.0f,  false);
         }

         if (ImGui::SliderInt("Sides", &m_numSides, 3, 100, "%i"))
         {
             m_pBoundaryMesh->CreateCircle(fw::vec2(0, 0), m_boundaryRad, m_numSides, 0.0f, false);
         }*/

        if (ImGui::Checkbox("VSync", &m_VSyncEnabled))
        {
            wglSwapInterval(m_VSyncEnabled ? 1 : 0);
        }

        m_SpawnEnemyTimer += deltaTime;

        if (m_SpawnEnemyTimer > 1.0f / m_CurrentLevel)
        {
            m_pEventManager->AddEvent(new SpawnNewEnemyEvent());
            m_SpawnEnemyTimer = 0.0f;
        }

        m_SpawnHPTimer += deltaTime;

        if (m_SpawnHPTimer > 10.0f)
        {
            SpawnHealthPickup(m_pPlayer->GetPosition(), m_boundaryRad);
            SpawnSmolBody(m_pPlayer->GetPosition(), m_boundaryRad);
            m_SpawnHPTimer = 0.0f;
        }

        ImGui::Text("Health: %d", m_PlayerHealth);
        //ImGui::Text("Alpha: %f", (float)m_PlayerHealth / 100);
        ImGui::Text("Level %d", m_CurrentLevel);
        ImGui::Text("Score: %d", (int)m_LevelTimer);

        m_LevelTimer += deltaTime;        

        if (m_LevelTimer > 15.0f)
            m_CurrentLevel = 2;

        if (m_LevelTimer > 45.0f)
            m_CurrentLevel = 3;

        if (m_PlayerHealth <= 0)
        {
            m_pEventManager->AddEvent(new GameOverEvent());            
        }

        if (m_IsSmolBodyTimerRunning == true)
        {
            m_SmolBodyTimer += deltaTime;

            if (m_SmolBodyTimer >= 5.0f)
            {
                m_CurrentBodyRadius = 0.25f;
                m_pCircleMesh->CreateCircle(fw::vec2(0, 0), m_CurrentBodyRadius, (m_PlayerHealth / 10) + 2, 0.0f, true);
                m_IsSmolBodyTimerRunning = false;
                m_SmolBodyTimer = 0.0f;
            }
        }
    }
    else
    {
        ImGui::Text("GAME OVER");
        ImGui::Text("Level %d", m_CurrentLevel);
        ImGui::Text("Score: %d", (int)m_LevelTimer);
        ImGui::Text("Dev HighScore: 103");
        ImGui::Text("Press R to Restart!");
    }

    if (m_pPlayerController->IsRestartHeld())
    {
        m_pEventManager->AddEvent(new RestartEvent());
    }
}

void Game::Draw()
{
    glClearColor(0.1, 0.1, 0.1, 1);
    glClear(GL_COLOR_BUFFER_BIT);

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

    if (pEvent->GetType() == SpawnNewEnemyEvent::GetStaticEventType())
    {
        SpawnEnemy(m_pPlayer->GetPosition(), m_boundaryRad);
    }

    if (pEvent->GetType() == GameOverEvent::GetStaticEventType())
    {
        m_PlayerState = PlayerState::Dead;
        m_CurrentBodyRadius = 0;
        m_pCircleMesh->CreateCircle(fw::vec2(0, 0), m_CurrentBodyRadius, (m_PlayerHealth / 10) + 2, 0.0f, true);
    }

    if (pEvent->GetType() == RestartEvent::GetStaticEventType())
    {
        m_PlayerState = PlayerState::Alive;
        m_CurrentBodyRadius = 0.25f;
        m_pCircleMesh->CreateCircle(fw::vec2(0, 0), m_CurrentBodyRadius, (m_PlayerHealth / 10) + 3, 0.0f, true);
        m_pPlayer->SetPosition(fw::vec2(5, 5));
        m_CurrentLevel = 1;
        m_PlayerHealth = 100;
        m_pPlayer->SetColor(fw::vec4::LightOrange(1.0f));
        m_SmolBodyTimer = 0.0f;
        m_IsSmolBodyTimerRunning = false;
        m_LevelTimer = 0.0f;

        for (int i = 0; i < m_gameObjects.size(); i++)
        {
            if ((m_gameObjects.at(i)->GetType() != fw::GameObject::Type::Player && m_gameObjects.at(i)->GetType() != fw::GameObject::Type::Default))
            {
                m_pEventManager->AddEvent(new RemoveFromGameEvent((m_gameObjects.at(i))));
            }
        }
    }

    //if (pEvent->GetType() == EnemyCollisionEvent::GetStaticEventType())
    //{
    //    m_pEventManager->AddEvent(new RemoveFromGameEvent((m_gameObjects.at(i))));
    //    m_PlayerHealth -= 10;
    //}
}

void Game::StartFrame(float deltaTime)
{
    //m_pImguiMan->StartFrame(deltaTime);
    
    m_pPlayerController->StartFrame();

    m_pEventManager->DispatchAllEvents(this);
}

void Game::Init()
{
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    m_pEventManager = new fw::EventManager();

    m_pImguiMan = new fw::ImGuiManager(m_pFramework);
    m_pImguiMan->Init();
    
    m_pShader = new fw::ShaderProgram("Data/Basic.vert", "Data/Basic.frag");

    m_pHumanMesh = new fw::Mesh();
    m_pHumanMesh->CreateShape(m_HumanVertices, m_HumanPrimitiveType, m_Humanattribs);    

    m_pBoundaryMesh = new fw::Mesh();
    m_pBoundaryMesh->CreateCircle(fw::vec2(0, 0), m_boundaryRad, m_numSides, 0.0f, false);

    m_pCircleMesh = new fw::Mesh();
    m_pCircleMesh->CreateCircle(fw::vec2(0, 0), m_CurrentBodyRadius, (m_PlayerHealth / 10) + 2, 0.0f, true);
    

    m_pPlayerController = new PlayerController();
    m_pPlayer = new Player(5.0f, 5.0f, "Circle", m_pPlayerController, m_pCircleMesh, m_pShader, fw::vec4::LightOrange(1.0f), this);
    
    fw::GameObject* m_pBoundary = new fw::GameObject(5.0f, 5.0f, "Boundary", m_pBoundaryMesh, m_pShader, fw::vec4::White(1), this, fw::GameObject::Type::Default);

    m_gameObjects.push_back(m_pPlayer);
    m_gameObjects.push_back(m_pBoundary);

    m_pEnemyMesh = new fw::Mesh();
    m_pEnemyMesh->CreateCircle(fw::vec2(0, 0), 0.2f, 4, 45.0f, true);

    m_pPickupMesh = new fw::Mesh();
    m_pPickupMesh->CreateCircle(fw::vec2(0, 0), 0.2, 6, 0.0f, true);

    //Settings
    wglSwapInterval(m_VSyncEnabled ? 1 : 0);
}

void Game::SpawnEnemy(fw::vec2 destination, float radius)
{
    Enemy* m_pNewEnemy = new Enemy(destination.x, destination.y, radius, "Enemy" + std::to_string(m_gameObjects.size()), m_pEnemyMesh, m_pShader, fw::vec4::Blue(0.75f), this);

    m_gameObjects.push_back(m_pNewEnemy);
}

void Game::SpawnHealthPickup(fw::vec2 destination, float radius)
{
    HealthPickup* pNewHP = new HealthPickup(destination.x, destination.y, radius, "Health Pickup", m_pPickupMesh, m_pShader, fw::vec4::Red(1.0f), this);

    m_gameObjects.push_back(pNewHP);
}

void Game::SpawnSmolBody(fw::vec2 destination, float radius)
{
    SmolBody* pNewSB = new SmolBody(destination.x, destination.y, radius, "Small Player Body", m_pPickupMesh, m_pShader, fw::vec4::Green(1.0f), this);

    m_gameObjects.push_back(pNewSB);
}
