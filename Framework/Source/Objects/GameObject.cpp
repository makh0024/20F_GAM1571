#include "Framework.h"
#include "GameObject.h"
#include "../../Libraries/imgui/imgui.h"

using namespace fw;

GameObject::GameObject(float x, float y, std::string Name, Mesh* Mesh, ShaderProgram* Shader, vec4 color, GameCore* pGameCore, Type objectType, vec2 scale)
{
	m_Pos = vec2(x,y);
	m_Color = color;

	m_pMesh = Mesh;
	m_pShader = Shader;

	m_pGameCore = pGameCore;

	m_Name = Name;

	m_objectType = objectType;

	m_Scale = scale;
}

GameObject::~GameObject()
{
}

void GameObject::Update(float deltaTime)
{
	
}

void GameObject::Draw()
{	
	m_pMesh->Draw(m_Pos, m_Scale, m_Pos, m_Color, m_pShader, m_pTexture, m_UVScale, m_UVOffset);
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

void GameObject::SetPosition(fw::vec2 newpos)
{
	m_Pos = newpos;
}

void fw::GameObject::SetColor(vec4 color)
{
	m_Color = color;
}

fw::vec2 GameObject::GetPosition()
{
	return fw::vec2(m_Pos);
}
