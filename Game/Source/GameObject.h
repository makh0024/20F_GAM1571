#pragma once

#include "Framework.h" //put in cpp and forward declare?

class GameObject
{
public:
	GameObject();
	~GameObject();

	void Update();
	void Draw();
	
protected:
	int m_x, m_y = 0;
	
	fw::Mesh* m_pMesh = nullptr;
	fw::ShaderProgram* m_pShader = nullptr;
};