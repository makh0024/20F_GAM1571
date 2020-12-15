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
			Bomb,
		};

		Type GetType() { return m_objectType; }
	public:
		GameObject(float x, float y, std::string Name, Mesh* Mesh, ShaderProgram* Shader, vec4 color, GameCore* pGameCore, Type objectType, vec2 scale);
		virtual ~GameObject();

		virtual void Update(float deltaTime);
		void Draw();

		void ChangeCameraPos(vec2 cameraPos);

		std::string GetName();

		void SetTexture(Texture* pTexture) { m_pTexture = pTexture; }

		void SetParameters(Mesh* Mesh, ShaderProgram* Shader);

		fw::vec2 GetPosition();
		void SetPosition(fw::vec2 newpos);

		void SetColor(vec4 color);

		void SetCanDraw(bool canDraw) { m_CanDraw = canDraw; }

	protected:
		fw::vec2 m_Pos = fw::vec2(0.0f, 0.0f);
		fw::vec2 m_Scale = fw::vec2(1.f, 1.f);
		fw::vec4 m_Color = fw::vec4(0, 0, 0, 0);

		fw::vec2 m_CameraPos = fw::vec2 (0.0f, 0.0f);

		Mesh* m_pMesh = nullptr;
		ShaderProgram* m_pShader = nullptr;

		GameCore* m_pGameCore = nullptr;

		std::string m_Name;

		Texture* m_pTexture = nullptr;

		Type m_objectType;

		vec2 m_UVScale = vec2(1, 1);
		vec2 m_UVOffset = vec2(0, 0);

		bool m_CanDraw = true;
	};
}