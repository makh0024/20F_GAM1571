#include "Framework.h"

#include "Game.h"

Game::Game(fw::FWCore* pFramework) : fw::GameCore(pFramework)
{
}

Game::~Game()
{
    delete m_pHumanMesh;
    delete m_pAnimalMesh;
    delete m_pShader;
}

void Game::Update(float deltaTime)
{
    float x = 1.0f / deltaTime;

    m_pImguiMan->StartFrame(deltaTime);
    ImGui::ShowDemoWindow();
}

void Game::Draw()
{
    /*m_pImguiMan->StartFrame(1);
    Imgui::ShowDemoWindow;*/

    glClearColor(0, 0, 0, 0);
    glClear(GL_COLOR_BUFFER_BIT);

    //m_pHumanoid->Draw();

    //m_pAnimal->Draw();
       
    for (int i = 0; i < m_gameObjects.size(); i++)
    {
        m_gameObjects.at(i)->Draw();
    }

    m_pImguiMan->EndFrame();
    //ImGuiManager::EndFrame;
}

void Game::Init()
{
    
    m_pImguiMan = new fw::ImGuiManager(m_pFramework);
    m_pImguiMan->Init();
    
    m_pShader = new fw::ShaderProgram("Data/Basic.vert", "Data/Basic.frag");

    //Human
    m_pHumanMesh = new fw::Mesh();
    
        // Define our triangle as 3 positions.
        float m_Humanattribs[] =
    {
        0.3f, 0.6f, // Face Left
        0.5f, 0.8f,
        0.5f, 0.3f,

        0.7f, 0.6f, // Face Right
        0.5f, 0.8f,
        0.5f, 0.3f,

        0.3f, 0.4f, // thas the body
        0.7f, 0.4f,
        0.5f, -0.3f,

        0.7f, -0.3f, // Leg down right
        0.6f, -0.7f,
        0.5f, -0.3f,

        0.5f, -0.3f, // Leg down left
        0.3f, -0.3f,
        0.4f, -0.7f,

        0.7f, -0.3f, // Leg up right
        0.6f, 0.1f,
        0.5f, -0.3f,

        0.3f, -0.3f, // Leg up left
        0.4f, 0.1f,
        0.5f, -0.3f,

        0.3f, 0.4f, // Left arm
        0.4f, 0.4f,
        0.2f, 0.0f,

        0.6f, 0.4f, // Right arm
        0.7f, 0.4f,
        0.8f, 0.0f,
    };

    int m_HumanVertices = 27;
    int m_HumanPrimitiveType = GL_TRIANGLES;

    //m_pHumanMesh->CreateHumanoid();
    m_pHumanMesh->CreateShape(m_HumanVertices, m_HumanPrimitiveType, m_Humanattribs);

    //Animal
    m_pAnimalMesh = new fw::Mesh();

    // Define our triangle as 3 positions.
    float m_Animalattribs[] =
    {
        -0.3f, 0.6f, // Tail
        -0.7f, 0.6f,

        -0.3f, 0.6f,
        -0.7f, 0.2f,

        -0.3f, 0.2f,
        -0.7f, 0.6f,

        -0.7f, 0.2f, // thas a body
        -0.7f, -0.4f,

        -0.3f, 0.2f,
        -0.3f, -0.4f,

        -0.3f, -0.4f,
        -0.5f, -0.6f,

        -0.7f, -0.4f,
        -0.5f, -0.6f,

        -0.5f, -0.45f, // Bone
        -0.5f, 0.2f,

        -0.5f, -0.4f,  //side bone
        -0.4f, -0.3f,

        -0.5f, -0.4f,
        -0.6f, -0.3f,

        -0.5f, 0.1f,
        -0.4f, 0.2f,

        -0.5f, 0.1f,
        -0.6f, 0.2f,

        -0.5f, 0.0f,
        -0.6f, 0.1f,

        -0.5f, 0.0f,
        -0.4f, 0.1f,

        -0.5f, -0.1f,
        -0.6f, 0.0f,

        -0.5f, -0.1f,
        -0.4f, 0.0f,

        -0.5f, -0.2f,
        -0.6f, -0.1f,

        -0.5f, -0.2f,
        -0.4f, -0.1f,

        -0.5f, -0.3f,
        -0.6f, -0.2f,

        -0.5f, -0.3f,
        -0.4f, -0.2f,
    };

    int m_AnimalVertices = 40;
    int m_AnimalPrimitiveType = GL_LINES;
    glLineWidth(5);

    //m_pAnimalMesh->CreateAnimal();
    m_pAnimalMesh->CreateShape(m_AnimalVertices, m_AnimalPrimitiveType, m_Animalattribs);

    //m_pHumanoid = new GameObject(m_pHumanMesh, m_pShader, 0, 0);
    //m_pAnimal = new GameObject(m_pAnimalMesh, m_pShader, 0, 0);

    for (int i = 0; i < 2; i++)
    {
        GameObject* gameObject = new GameObject(0.0f, 0.0f);
        m_gameObjects.push_back(gameObject);
    }

    m_gameObjects.at(0)->SetParameters(m_pHumanMesh, m_pShader);
    m_gameObjects.at(1)->SetParameters(m_pAnimalMesh, m_pShader);
}
