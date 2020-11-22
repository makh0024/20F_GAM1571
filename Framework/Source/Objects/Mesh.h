#pragma once
#include "Math/Vector.h"

namespace fw 
{
	class ShaderProgram;
	class Texture;

	struct VertexFormat
	{
		float x;
		float y;
		float u;
		float v;

		VertexFormat(float nx, float ny, float nu, float nv)
		{
			x = nx;
			y = ny;
			u = nu;
			v = nv;
		}
	};

	class Mesh
	{
	public:
		Mesh();
		Mesh(int primitiveType, int numVertices, const VertexFormat* pVertices);
		~Mesh();

		void Draw(vec2 pos, vec4 color, ShaderProgram* Shader, Texture* pTexture, vec2 UVScale, vec2 UVOffset);

		//void CreateHumanoid();
		//void CreateAnimal();

		void CreateShape(const int NumVertices, const int PrimitiveType, const VertexFormat* attribs);

		void CreateCircle(vec2 centerPos, float radius, int NumVertices, float Offset, bool IsFilled);

		void SetUniform1f(ShaderProgram* pShader, char* name, float value);

		void SetUniform2f(ShaderProgram* pShader, char* name, vec2 position);

		void SetUniform4f(ShaderProgram* pShader, char* name, vec4 color);

		void SetUniform1i(ShaderProgram* pShader, char* name, int value);

	protected:
		GLuint m_VBO = 0;

		int m_NumVertices = 0;
		int m_PrimitiveType = GL_POINTS;
	};
} // namespace fw
