#pragma once

class Player;
class PlayerController;
class Tilemap;
class Pathfinder;
class Enemy;
class Bomb;

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

    Player* GetPlayer() { return m_pPlayer;  }
protected:

    std::vector<fw::GameObject*> m_gameObjects;
    std::vector<Bomb*> m_pBombs;


    fw::ImGuiManager* m_pImguiMan = nullptr;

    std::map<std::string, fw::Mesh*> m_pMeshs;
    std::map<std::string, fw::ShaderProgram*> m_pShaders;
    std::map<std::string, fw::Texture*> m_pTextures;

    fw::Spritesheet* m_pSpritesheet;

    Player* m_pPlayer = nullptr;
    //Player* m_pPlayer2 = nullptr;

    float m_boundaryRad;
    int m_numSides;

    fw::FWCore* m_pFramework = nullptr;

    PlayerController* m_pPlayerController; 

    Tilemap* m_pTilemap;

    Pathfinder* m_pPathfinder;

    Enemy* m_pEnemy;

    Bomb* m_pBomb;

    Bomb* m_pBombEnemy;
    //Settings
    bool m_VSyncEnabled = true;
};