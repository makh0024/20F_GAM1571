#pragma once

#include "Characters/Player.h"
#include "Characters/Shapes.h"
#include "Characters/Enemy.h"

class PlayerController;

class Game : public fw::GameCore
{
public:
    Game(fw::FWCore* pFramework);
    virtual ~Game();
    virtual void Update(float deltaTime) override;
    virtual void Draw() override;

    virtual void OnEvent(fw::Event* pEvent) override;
    virtual void StartFrame(float deltaTime) override;

    void Init();

    void SpawnEnemy(fw::vec2 destination, float radius);

    Player* GetPlayer() { return m_pPlayer;  }
protected:
    fw::ShaderProgram* m_pShader = nullptr;
    fw::Mesh* m_pHumanMesh = nullptr;
    fw::Mesh* m_pAnimalMesh = nullptr;
    
    fw::Mesh* m_pBoundaryMesh = nullptr;
    fw::Mesh* m_pCircleMesh = nullptr;
    fw::Mesh* m_pEnemyMesh = nullptr;

    std::vector<fw::GameObject*> m_gameObjects;

    fw::ImGuiManager* m_pImguiMan = nullptr;

    Player* m_pPlayer = nullptr;

    float m_boundaryRad;
    int m_numSides;

    fw::FWCore* m_pFramework = nullptr;

    PlayerController* m_pPlayerController;

    //Settings
    bool m_VSyncEnabled = true;

    float m_SpawnEnemyTimer;

    std::vector<Enemy*> m_pEnemies;
};