#pragma once

#include "Characters/Player.h"

class Game : public fw::GameCore
{
public:
    Game(fw::FWCore* pFramework);
    virtual ~Game();
    virtual void Update(float deltaTime) override;
    virtual void Draw() override;

    void Init();

protected:
    fw::ShaderProgram* m_pShader = nullptr;
    fw::Mesh* m_pHumanMesh = nullptr;
    fw::Mesh* m_pAnimalMesh = nullptr;
    //GameObject* m_pHumanoid = nullptr;
    //GameObject* m_pAnimal = nullptr;

    std::vector<fw::GameObject*> m_gameObjects;

    fw::ImGuiManager* m_pImguiMan = nullptr;
    //fw::FWCore* pCore;

    Player* m_pPlayer = nullptr;

    fw::FWCore* m_pFramework = nullptr;
};