#include "FrameworkPCH.h"
#include "Mesh.h"
#include "Utility/ShaderProgram.h"
#include "Utility/Helpers.h"

namespace fw {

    Mesh::Mesh()
    {
    }

    Mesh::~Mesh()
    {
        glDeleteBuffers(1, &m_VBO);
    }

    void Mesh::Draw(vec2 pos, ShaderProgram* Shader)
    {
        glUseProgram(Shader->GetProgram()); 

        // Set this VBO to be the currently active one.
        glBindBuffer(GL_ARRAY_BUFFER, m_VBO);

        // Get the attribute variable?s location from the shader.
        GLint loc = 0; //glGetAttribLocation( m_pShader->m_Program, "a_Position" );
        glEnableVertexAttribArray(loc);

        // Describe the attributes in the VBO to OpenGL.
        glVertexAttribPointer(loc, 2, GL_FLOAT, GL_FALSE, 8, (void*)0);

        //assert(x == 0.0f);
        //Setup our uniforms
        {
            SetUniform1f(Shader, "u_Time", (float)GetSystemTimeSinceGameStart());
            SetUniform2f(Shader, "u_Increment", pos);
            /*int timeLocation = glGetUniformLocation(Shader->GetProgram(), "u_Time");
            glUniform1f(timeLocation, GetSystemTimeSinceGameStart());*/
        }

        // Draw the primitive.
        glDrawArrays(m_PrimitiveType, 0, m_NumVertices);
    }

    void Mesh::CreateShape(int NumVertices, int PrimitiveType, float* attribs)
    {
        // Generate a buffer for our vertex attributes.
        glGenBuffers(1, &m_VBO); // m_VBO is a GLuint.

        // Set this VBO to be the currently active one.
        glBindBuffer(GL_ARRAY_BUFFER, m_VBO);

        m_NumVertices = NumVertices;
        m_PrimitiveType = PrimitiveType;
        //glLineWidth(5);

        //float m_attribs = attribs;

        // Copy our attribute data into the VBO.
        int numAttributeComponents = m_NumVertices * 2; // x & y for each vertex.
        glBufferData(GL_ARRAY_BUFFER, sizeof(float) * numAttributeComponents, attribs, GL_STATIC_DRAW);
    }

    void Mesh::SetUniform1f(ShaderProgram* pShader, char* name, float value)
    {
        int loc = glGetUniformLocation(pShader->GetProgram(), name);
        glUniform1f(loc, value);
    }

    void Mesh::SetUniform2f(ShaderProgram* pShader, char* name, vec2 position)
    {
        float loc = glGetUniformLocation(pShader->GetProgram(), name);
        glUniform2f(loc, position.m_x, position.m_y);
    }

} // namespace fw