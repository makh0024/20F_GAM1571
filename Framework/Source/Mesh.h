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

		void CreateHumanoid();
		void CreateAnimal();

	protected:
		GLuint m_VBO = 0;

		int m_NumVertices = 0;
		int m_PrimitiveType = GL_POINTS;
	};
} // namespace fw
