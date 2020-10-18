#pragma once
#include "Math/Vector.h"

namespace fw 
{
	class ShaderProgram;

	class Mesh
	{
	public:
		Mesh();
		~Mesh();

		void Draw(vec2 pos, vec4 color, ShaderProgram* Shader);

		//void CreateHumanoid();
		//void CreateAnimal();

		void CreateShape(const int NumVertices, const int PrimitiveType, const float* attribs);

		void CreateCircle(vec2 centerPos, float radius, int NumVertices, float Offset, bool IsFilled);

		void SetUniform1f(ShaderProgram* pShader, char* name, float value);

		void SetUniform2f(ShaderProgram* pShader, char* name, vec2 position);

		void SetUniform4f(ShaderProgram* pShader, char* name, vec4 color);

	protected:
		GLuint m_VBO = 0;

		int m_NumVertices = 0;
		int m_PrimitiveType = GL_POINTS;
	};
} // namespace fw
