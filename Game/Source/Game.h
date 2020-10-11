#pragma once

#include "Characters/Player.h"
#include "Characters/Shapes.h"

class Game : public fw::GameCore
{
public:
    Game(fw::FWCore* pFramework);
    virtual ~Game();
    virtual void Update(float deltaTime) override;
    virtual void Draw() override;
    virtual void OnEvent(fw::Event* pEvent) override;

    void Init();

protected:
    fw::ShaderProgram* m_pShader = nullptr;
    fw::Mesh* m_pHumanMesh = nullptr;
    fw::Mesh* m_pAnimalMesh = nullptr;
    fw::Mesh* m_CircleMesh = nullptr;

    std::vector<fw::GameObject*> m_gameObjects;

    fw::EventManager* m_pEventManager = nullptr;
    fw::ImGuiManager* m_pImguiMan = nullptr;

    Player* m_pPlayer = nullptr;


    fw::FWCore* m_pFramework = nullptr;
};