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
    fw::Mesh* m_pMesh = nullptr;
};