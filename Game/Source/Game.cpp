#include "Framework.h"

#include "Game.h"

Game::~Game()
{
}

void Game::Update()
{
}

void Game::Draw()
{
    glClearColor(0, 1, 0, 0);
    glClear(GL_COLOR_BUFFER_BIT);
}

void Game::Init()
{
    m_pShader = new fw::ShaderProgram("Data/Basic.vert", "Data/Basic.frag");
}
