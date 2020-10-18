#pragma once 
#include "Math/Vector.h"

namespace fw {

	class GameObject
	{
	public:
		GameObject(float x, float y, std::string Name, Mesh* Mesh, ShaderProgram* Shader, vec4 color, GameCore* pGameCore);
		~GameObject();

		virtual void Update(float deltaTime);
		void Draw();

		std::string GetName();

		void SetParameters(Mesh* Mesh, ShaderProgram* Shader);

		fw::vec2 GetPosition();
		void SetPosition(fw::vec2 newpos);
	protected:
		fw::vec2 m_Pos = fw::vec2(0.0f, 0.0f);
		fw::vec4 m_Color = fw::vec4(0, 0, 0, 0);

		Mesh* m_pMesh = nullptr;
		ShaderProgram* m_pShader = nullptr;

		GameCore* m_pGameCore = nullptr;

		std::string m_Name;
	};
}