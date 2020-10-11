#include "Framework.h"
#include "GameObject.h"
#include "../../Libraries/imgui/imgui.h"


using namespace fw;

GameObject::GameObject(float x, float y, std::string Name, Mesh* Mesh, ShaderProgram* Shader,  GameCore* pGameCore)
{
	m_Pos = vec2(x,y);

	m_pMesh = Mesh;
	m_pShader = Shader;

	m_pGameCore = pGameCore;

	m_Name = Name;
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

std::string fw::GameObject::GetName()
{
	return std::string(m_Name);
}

void GameObject::SetParameters(Mesh* Mesh, ShaderProgram* Shader)
{
	m_pMesh = Mesh;
	m_pShader = Shader;
}