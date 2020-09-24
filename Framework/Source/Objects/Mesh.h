#pragma once

namespace fw 
{
	class ShaderProgram;

	class Mesh
	{
	public:
		Mesh();
		~Mesh();

		void Draw(ShaderProgram* Shader);

		//void CreateHumanoid();
		//void CreateAnimal();

		void CreateShape(int NumVertices, int PrimitiveType, float* attribs);

		void SetUniform1f(ShaderProgram* pShader, char* name, float value);

	protected:
		GLuint m_VBO = 0;

		int m_NumVertices = 0;
		int m_PrimitiveType = GL_POINTS;
	};
} // namespace fw
