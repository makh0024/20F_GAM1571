#include "GamePCH.h"

#include "Game.h"

#include "Events/GameEvents.h"


Game::Game(fw::FWCore* pFramework) : fw::GameCore(pFramework)
{
    m_pFramework = pFramework;
    m_boundaryRad = 3.0f;
    m_numSides = 3.0;
}

Game::~Game()
{
    delete m_pHumanMesh;
    delete m_pAnimalMesh;
    delete m_pShader;

    delete m_pEventManager;
    delete m_pImguiMan; 
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
        ImGui::PopID();
    }

    //static float f1 = 3.0f;
    if (ImGui::SliderFloat("Radius", &m_boundaryRad, 0.0f, 5.0f, "%f"))
    {
        m_pBoundaryMesh->CreateCircle(fw::vec2(0, 0), m_boundaryRad, m_numSides, false);
    }

    if (ImGui::SliderInt("Sides", &m_numSides, 3, 100, "%i"))
    {
        m_pBoundaryMesh->CreateCircle(fw::vec2(0, 0), m_boundaryRad, m_numSides, false);
    }
}

void Game::Draw()
{
    glClearColor(0, 0, 0, 0);
    glClear(GL_COLOR_BUFFER_BIT);

    for (int i = 0; i < m_gameObjects.size(); i++)
    {
        m_gameObjects.at(i)->Draw();
    }

    m_pImguiMan->EndFrame();
}

void Game::OnEvent(fw::Event* pEvent)
{
    if (pEvent->GetType() == RemoveFromGameEvent::GetStaticEventType())
    {
        RemoveFromGameEvent* pRemoveFromGameEvent = static_cast<RemoveFromGameEvent*>(pEvent);
        fw::GameObject* pObject = pRemoveFromGameEvent->GetGameObject();

        auto it = std::find(m_gameObjects.begin(), m_gameObjects.end(), pObject);
        m_gameObjects.erase(it);

        delete pObject;
    }
}

void Game::Init()
{
    m_pEventManager = new fw::EventManager();

    m_pImguiMan = new fw::ImGuiManager(m_pFramework);
    m_pImguiMan->Init();
    
    m_pShader = new fw::ShaderProgram("Data/Basic.vert", "Data/Basic.frag");

    m_pHumanMesh = new fw::Mesh();
    m_pHumanMesh->CreateShape(m_HumanVertices, m_HumanPrimitiveType, m_Humanattribs);    

    m_pBoundaryMesh = new fw::Mesh();
    m_pBoundaryMesh->CreateCircle(fw::vec2(0, 0), m_boundaryRad, m_numSides, false);

    m_pCircleMesh = new fw::Mesh();
    m_pCircleMesh->CreateCircle(fw::vec2(0, 0), 0.25f, 15, true);

    m_pPlayer = new Player(5.0f, 5.0f, "Circle", m_pCircleMesh, m_pShader, this);
    
    fw::GameObject* m_pBoundary = new fw::GameObject(5.0f, 5.0f, "Boundary", m_pBoundaryMesh, m_pShader, this);

    m_gameObjects.push_back(m_pPlayer);
    m_gameObjects.push_back(m_pBoundary);
}
