#include "GameObject.h"

GameObject::GameObject(int x, int y) :
	m_x(0),
	m_y(0)
{

}

GameObject::~GameObject()
{
}

void GameObject::Update()
{
}

void GameObject::Draw()
{	
	m_pMesh->Draw(m_pShader);
}

void GameObject::SetParameters(Mesh* Mesh, ShaderProgram* Shader)
{
	m_pMesh = Mesh;
	m_pShader = Shader;
}
