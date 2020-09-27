#include "Framework.h"
#include "GameObject.h"

using namespace fw;

GameObject::GameObject(float x, float y, Mesh* Mesh, ShaderProgram* Shader,  GameCore* pGameCore)
{
	m_Pos = vec2(x,y);

	m_pMesh = Mesh;
	m_pShader = Shader;

	m_pGameCore = pGameCore;
}

GameObject::~GameObject()
{
}

void GameObject::Update(float deltaTime)
{
	
}

void GameObject::Draw()
{	
	m_pMesh->Draw(m_Pos, m_pShader);
}

void GameObject::SetParameters(Mesh* Mesh, ShaderProgram* Shader)
{
	m_pMesh = Mesh;
	m_pShader = Shader;
}