#include "GameObject.h"

GameObject::GameObject()
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
	glUseProgram(m_pShader->GetProgram());
	m_pMesh->Draw();

}
