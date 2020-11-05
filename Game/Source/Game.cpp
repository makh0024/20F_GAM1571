#include "GamePCH.h"

#include "Game.h"

#include "Events/GameEvents.h"

#include "Characters/PlayerController.h"

Game::Game(fw::FWCore* pFramework) : fw::GameCore(pFramework)
{
    m_pFramework = pFramework;
    m_boundaryRad = 3.0f;
    m_numSides = 50;
    m_SpawnEnemyTimer = 0.0f;
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
    //delete m_pEnemyMesh;
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

    for (int i = 0; i < m_gameObjects.size(); i++)
    {
        m_gameObjects.at(i)->Update(deltaTime);

        ImGui::PushID(m_gameObjects.at(i));
        ImGui::Text("Name: %s", m_gameObjects.at(i)->GetName().c_str());
        ImGui::SameLine();
        if (ImGui::Button("Delete"))
        {
            m_pEventManager->AddEvent(new RemoveFromGameEvent((m_gameObjects.at(i))));
        }

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
            if ((m_pPlayer->GetPosition() - m_gameObjects.at(i)->GetPosition()).Magnitude() <= 0.4f)
            {
                m_pEventManager->AddEvent(new RemoveFromGameEvent((m_gameObjects.at(i))));
            }
        }
        ImGui::PopID();
    }

    if (ImGui::SliderFloat("Radius", &m_boundaryRad, 0.0f, 5.0f, "%f"))
    {
        m_pBoundaryMesh->CreateCircle(fw::vec2(0, 0), m_boundaryRad, m_numSides, 0.0f,  false);
    }

    if (ImGui::SliderInt("Sides", &m_numSides, 3, 100, "%i"))
    {
        m_pBoundaryMesh->CreateCircle(fw::vec2(0, 0), m_boundaryRad, m_numSides, 0.0f, false);
    }

    if (ImGui::Checkbox("VSync", &m_VSyncEnabled))
    {
        wglSwapInterval(m_VSyncEnabled ? 1 : 0);
    }

    m_SpawnEnemyTimer += deltaTime;

    if (m_SpawnEnemyTimer > 0.75f)
    {
        m_pEventManager->AddEvent(new SpawnNewEnemyEvent());
        m_SpawnEnemyTimer = 0.0f;
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

    for (int i = 0; i < m_pEnemies.size(); i++)
    {
        m_pEnemies.at(i)->Draw();
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
    m_pCircleMesh->CreateCircle(fw::vec2(0, 0), 0.25f, 25, 0.0f, true);
    

    m_pPlayerController = new PlayerController();
    m_pPlayer = new Player(5.0f, 5.0f, "Circle", m_pPlayerController, m_pCircleMesh, m_pShader, fw::vec4::LightOrange(0.9f), this);
    
    fw::GameObject* m_pBoundary = new fw::GameObject(5.0f, 5.0f, "Boundary", m_pBoundaryMesh, m_pShader, fw::vec4::White(1), this, fw::GameObject::Type::Default);

    m_gameObjects.push_back(m_pPlayer);
    m_gameObjects.push_back(m_pBoundary);

    m_pEnemyMesh = new fw::Mesh();
    m_pEnemyMesh->CreateCircle(fw::vec2(0, 0), 0.2f, 4, 45.0f, true);
    //Settings
    wglSwapInterval(m_VSyncEnabled ? 1 : 0);
}

void Game::SpawnEnemy(fw::vec2 destination, float radius)
{
    Enemy* m_pNewEnemy = new Enemy(destination.x, destination.y, m_boundaryRad, "Enemy" + std::to_string(m_gameObjects.size()), m_pEnemyMesh, m_pShader, fw::vec4::Blue(0.75f), this);

    m_gameObjects.push_back(m_pNewEnemy);

    //delete pEnemyMesh;
}
