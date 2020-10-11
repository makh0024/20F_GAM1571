#include "GamePCH.h"

#include "Game.h"

#include "Events/GameEvents.h"


Game::Game(fw::FWCore* pFramework) : fw::GameCore(pFramework)
{
    m_pFramework = pFramework;
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
        ImGui::Text("Name: %s", m_pPlayer->GetName().c_str());
        ImGui::SameLine();
        if (ImGui::Button("Delete"))
        {
            m_gameObjects.erase(m_gameObjects.begin() + i);
            m_pEventManager->AddEvent(new RemoveFromGameEvent((m_gameObjects.at(i))));
        }
        ImGui::PopID();
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

    m_CircleMesh = new fw::Mesh();
    m_CircleMesh->CreateCircle(fw::vec2(0, 0), 3.0f, 15);

    m_pPlayer = new Player(5.0f, 5.0f, "Human", m_CircleMesh, m_pShader, this);


    m_gameObjects.push_back(m_pPlayer);
    
}
