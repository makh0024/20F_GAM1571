#include "FrameworkPCH.h"
#include "Mesh.h"
#include "Constants.h"
#include "Utility/ShaderProgram.h"

namespace fw {

    Mesh::Mesh()
    {
    }

    Mesh::~Mesh()
    {
        glDeleteBuffers(1, &m_VBO);
    }

    void Mesh::Draw(ShaderProgram* Shader)
    {
        glUseProgram(Shader->GetProgram()); 

        // Set this VBO to be the currently active one.
        glBindBuffer(GL_ARRAY_BUFFER, m_VBO);

        // Get the attribute variable?s location from the shader.
        GLint loc = 0; //glGetAttribLocation( m_pShader->m_Program, "a_Position" );
        glEnableVertexAttribArray(loc);

        // Describe the attributes in the VBO to OpenGL.
        glVertexAttribPointer(loc, 2, GL_FLOAT, GL_FALSE, 8, (void*)0);

        // Draw the primitive.
        glDrawArrays(m_PrimitiveType, 0, m_NumVertices);
    }

    void Mesh::CreateAnimal()
    {
        // Generate a buffer for our vertex attributes.
        glGenBuffers(1, &m_VBO); // m_VBO is a GLuint.

        // Set this VBO to be the currently active one.
        glBindBuffer(GL_ARRAY_BUFFER, m_VBO);

        // Define our triangle as 3 positions.
        float attribs[] =
        {
            -0.3f, 0.6f, // Tail
            -0.7f, 0.6f, 

            -0.3f, 0.6f, 
            -0.7f, 0.2f,

            -0.3f, 0.2f,
            -0.7f, 0.6f,

            -0.7f, 0.2f, // thas a body
            -0.7f, -0.4f,

            -0.3f, 0.2f,
            -0.3f, -0.4f,

            -0.3f, -0.4f,
            -0.5f, -0.6f,
           
            -0.7f, -0.4f,
            -0.5f, -0.6f,

            -0.5f, -0.45f, // Bone
            -0.5f, 0.2f,

            -0.5f, -0.4f,  //side bone
            -0.4f, -0.3f,

            -0.5f, -0.4f,
            -0.6f, -0.3f,

            -0.5f, 0.1f,
            -0.4f, 0.2f,

            -0.5f, 0.1f,
            -0.6f, 0.2f,

            -0.5f, 0.0f,
            -0.6f, 0.1f,

            -0.5f, 0.0f,
            -0.4f, 0.1f,

            -0.5f, -0.1f,
            -0.6f, 0.0f,

            -0.5f, -0.1f,
            -0.4f, 0.0f,

            -0.5f, -0.2f,
            -0.6f, -0.1f,

            -0.5f, -0.2f,
            -0.4f, -0.1f,

            -0.5f, -0.3f,
            -0.6f, -0.2f,

            -0.5f, -0.3f,
            -0.4f, -0.2f,
        };

        m_NumVertices = 40;
        m_PrimitiveType = GL_LINES;
        glLineWidth(5);

        // Copy our attribute data into the VBO.
        int numAttributeComponents = m_NumVertices * 2; // x & y for each vertex.
        glBufferData(GL_ARRAY_BUFFER, sizeof(float) * numAttributeComponents, attribs, GL_STATIC_DRAW);
    }

    void Mesh::CreateHumanoid()
    {
        // Generate a buffer for our vertex attributes.
        glGenBuffers(1, &m_VBO); // m_VBO is a GLuint.

        // Set this VBO to be the currently active one.
        glBindBuffer(GL_ARRAY_BUFFER, m_VBO);

        // Define our triangle as 3 positions.
        float attribs[] =
        {
            0.3f, 0.6f, // Face Left
            0.5f, 0.8f, 
            0.5f, 0.3f, 

            0.7f, 0.6f, // Face Right
            0.5f, 0.8f, 
            0.5f, 0.3f, 

            0.3f, 0.4f, // thas the body
            0.7f, 0.4f, 
            0.5f, -0.3f, 

            0.7f, -0.3f, // Leg down right
            0.6f, -0.7f, 
            0.5f, -0.3f, 

            0.5f, -0.3f, // Leg down left
            0.3f, -0.3f, 
            0.4f, -0.7f, 

            0.7f, -0.3f, // Leg up right
            0.6f, 0.1f, 
            0.5f, -0.3f, 

            0.3f, -0.3f, // Leg up left
            0.4f, 0.1f, 
            0.5f, -0.3f,

            0.3f, 0.4f, // Left arm
            0.4f, 0.4f,
            0.2f, 0.0f,

            0.6f, 0.4f, // Right arm
            0.7f, 0.4f,
            0.8f, 0.0f,
        };

        m_NumVertices = 27;
        m_PrimitiveType = GL_TRIANGLES;
        

        // Copy our attribute data into the VBO.
        int numAttributeComponents = m_NumVertices * 2; // x & y for each vertex.
        glBufferData(GL_ARRAY_BUFFER, sizeof(float) * numAttributeComponents, attribs, GL_STATIC_DRAW);
    }

} // namespace fw