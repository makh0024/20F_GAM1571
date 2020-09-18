#include "Framework.h"

#include "Game.h"

Game::Game()
{
}

Game::~Game()
{
    //delete m_pHumanMesh;
    //delete m_pAnimalMesh;
    delete m_pShader;


}

void Game::Update()
{
}

void Game::Draw()
{
    glClearColor(0, 0, 0, 0);
    glClear(GL_COLOR_BUFFER_BIT);

    //m_pHumanoid->Draw();

    //m_pAnimal->Draw();
       
    for (int i = 0; i < m_gameObjects.size(); i++)
    {
        m_gameObjects.at(i)->Draw();
    }
}

void Game::Init()
{
    m_pShader = new fw::ShaderProgram("Data/Basic.vert", "Data/Basic.frag");

    m_pHumanMesh = new fw::Mesh();
    m_pHumanMesh->CreateHumanoid();

    m_pAnimalMesh = new fw::Mesh();
    m_pAnimalMesh->CreateAnimal();

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
