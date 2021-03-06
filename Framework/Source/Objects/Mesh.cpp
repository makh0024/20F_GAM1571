#include "FrameworkPCH.h"
#include "Mesh.h"
#include "Utility/ShaderProgram.h"
#include "Utility/Helpers.h"
#include "Objects/Texture.h"

namespace fw {

    Mesh::Mesh()
    {
    }

    Mesh::Mesh(int primitiveType, int numVertices, const VertexFormat* pVertices)
    {
        CreateShape(numVertices, primitiveType, pVertices);
    }

    Mesh::~Mesh()
    {
        glDeleteBuffers(1, &m_VBO);
    }

    void Mesh::Draw(vec2 pos, vec2 scale, vec2 camera, vec4 color, ShaderProgram* Shader, Texture* pTexture, vec2 UVScale, vec2 UVOffset)
    {
        glUseProgram(Shader->GetProgram()); 

        // Set this VBO to be the currently active one.
        glBindBuffer(GL_ARRAY_BUFFER, m_VBO);

        // Get the attribute variable?s location from the shader.
        //GLint loc = 0; //glGetAttribLocation( m_pShader->m_Program, "a_Position" );
        //glEnableVertexAttribArray(loc);

        GLint loc = glGetAttribLocation(Shader->GetProgram(), "a_Position");
        if (loc != -1)
        {
            glEnableVertexAttribArray(loc);
            glVertexAttribPointer(loc, 2, GL_FLOAT, GL_FALSE, 16, (void*)0);
        }

        // Describe the attributes in the VBO to OpenGL.
        loc = glGetAttribLocation(Shader->GetProgram(), "a_UVCoord");
        if (loc != -1)
        {
            glEnableVertexAttribArray(loc);
            glVertexAttribPointer(loc, 2, GL_FLOAT, GL_FALSE, 16, (void*)8);
        }

        //assert(x == 0.0f);
        //Setup our uniforms
        {
            SetUniform1f(Shader, "u_Time", (float)GetSystemTimeSinceGameStart());
            SetUniform2f(Shader, "u_ObjectScale", scale);
            SetUniform2f(Shader, "u_CameraPos", camera);
            SetUniform2f(Shader, "u_ObjectPos", pos);
            SetUniform4f(Shader, "u_Color", color);

            SetUniform2f(Shader, "u_UVScale", UVScale);
            SetUniform2f(Shader, "u_UVOffset", UVOffset);

            if (pTexture != nullptr)
            {
                glActiveTexture(GL_TEXTURE0);
                glBindTexture(GL_TEXTURE_2D, pTexture->GetHandle());
                SetUniform1i(Shader, "u_Texture", 0);
            }
        }

        // Draw the primitive.
        glDrawArrays(m_PrimitiveType, 0, m_NumVertices);
    }

    void Mesh::CreateShape(const int NumVertices, const int PrimitiveType, const VertexFormat* attribs)
    {
        // delete if we have an exisiting buffer
        glDeleteBuffers(1, &m_VBO);
        
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
        glBufferData(GL_ARRAY_BUFFER, sizeof(VertexFormat) * m_NumVertices, attribs, GL_STATIC_DRAW);
    }

    void Mesh::CreateCircle(vec2 centerPos, float radius, int NumVertices, float Offset, bool IsFilled)
    {
        if (NumVertices < 2)
        {
            return;
        }

        std::vector<float> m_Vertices;

        float angleOffset = Offset * 3.1415926f / 180.0f;

        float angle = (2 * 3.1415926f / NumVertices);
        
        for (int i = 0; i < NumVertices; i++)
        {
            vec2 prvtemp = vec2(radius * sin(angle * (i + 1) + angleOffset), radius * cos(angle * (i + 1) + angleOffset));
            vec2 temp = vec2(radius * sin(angle * (i + 2) + angleOffset), radius * cos(angle * (i + 2) + angleOffset));

            m_Vertices.push_back(prvtemp.x);
            m_Vertices.push_back(prvtemp.y);

            m_Vertices.push_back(temp.x);
            m_Vertices.push_back(temp.y);
            
            if (IsFilled) 
            {
                m_Vertices.push_back(centerPos.y);
                m_Vertices.push_back(centerPos.x);
            }
        }

        // Generate a buffer for our vertex attributes.
        glGenBuffers(1, &m_VBO); // m_VBO is a GLuint.

        // Set this VBO to be the currently active one.
        glBindBuffer(GL_ARRAY_BUFFER, m_VBO);

        m_NumVertices = (int)(m_Vertices.size() / 2);

        if (IsFilled)       
            m_PrimitiveType = GL_TRIANGLES;
        else        
            m_PrimitiveType = GL_LINES;        

        glLineWidth(5.0f);

        // Copy our attribute data into the VBO.
        int numAttributeComponents = m_NumVertices * 2; // x & y for each vertex.
        glBufferData(GL_ARRAY_BUFFER, sizeof(float) * numAttributeComponents, &m_Vertices[0], GL_STATIC_DRAW);
    }

    void Mesh::SetUniform1f(ShaderProgram* pShader, char* name, float value)
    {
        int loc = glGetUniformLocation(pShader->GetProgram(), name);
        glUniform1f(loc, value);
    }

    void Mesh::SetUniform2f(ShaderProgram* pShader, char* name, vec2 position)
    {
        GLint loc = glGetUniformLocation(pShader->GetProgram(), name);
        glUniform2f(loc, position.x, position.y);
    }

    void Mesh::SetUniform4f(ShaderProgram* pShader, char* name, vec4 color)
    {
        GLint loc = glGetUniformLocation(pShader->GetProgram(), name);
        glUniform4f(loc, color.x, color.y, color.z, color.w);
    }

    void Mesh::SetUniform1i(ShaderProgram* pShader, char* name, int value)
    {
        int loc = glGetUniformLocation(pShader->GetProgram(), name);
        glUniform1i(loc, value);
    }
} // namespace fw