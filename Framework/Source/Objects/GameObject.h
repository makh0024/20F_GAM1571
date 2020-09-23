#pragma once

#include "Framework.h" 

using namespace fw;

class GameObject
{
public:
	GameObject(int x, int y);
	~GameObject();

	void Update();
	void Draw();

	void SetParameters(Mesh* Mesh, ShaderProgram* Shader);

	
protected:
	int m_x, m_y;
	
	Mesh* m_pMesh = nullptr;
	ShaderProgram* m_pShader = nullptr;
};