#pragma once 
#include "Math/Vector.h"

namespace fw {

	class Texture;


	class GameObject
	{
	public:
		enum class Type
		{
			Default,
			Player,
			Enemy,
			HealthPickup,
			SmolBody,
		};

		Type GetType() { return m_objectType; }
	public:
		GameObject(float x, float y, std::string Name, Mesh* Mesh, ShaderProgram* Shader, vec4 color, GameCore* pGameCore, Type objectType);
		~GameObject();

		virtual void Update(float deltaTime);
		void Draw();

		std::string GetName();

		void SetTexture(Texture* pTexture) { m_pTexture = pTexture; }

		void SetParameters(Mesh* Mesh, ShaderProgram* Shader);

		fw::vec2 GetPosition();
		void SetPosition(fw::vec2 newpos);

		void SetColor(vec4 color);

	protected:
		fw::vec2 m_Pos = fw::vec2(0.0f, 0.0f);
		fw::vec4 m_Color = fw::vec4(0, 0, 0, 0);

		Mesh* m_pMesh = nullptr;
		ShaderProgram* m_pShader = nullptr;

		GameCore* m_pGameCore = nullptr;

		std::string m_Name;

		Texture* m_pTexture = nullptr;

		Type m_objectType;

		vec2 m_UVScale = vec2(1, 1);
		vec2 m_UVOffset = vec2(0, 0);
	};
}