#pragma once

class Game : public fw::GameCore
{
public:
    Game();
    virtual ~Game();
    virtual void Update() override;
    virtual void Draw() override;

    void Init();

protected:
    fw::ShaderProgram* m_pShader = nullptr;
    fw::Mesh* m_pHumanMesh = nullptr;
    fw::Mesh* m_pAnimalMesh = nullptr;
    GameObject* m_pHumanoid = nullptr;
    GameObject* m_pAnimal = nullptr;

    //std::vector<GameObject*> m_gameObjects;
};