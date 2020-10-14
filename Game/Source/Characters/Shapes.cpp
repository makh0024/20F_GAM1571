#include "GamePCH.h"

#include "Shapes.h"


const float m_Humanattribs[] =
{
    (0.3f - 0.5f), 0.6f, // Face Left
    (0.5f - 0.5f), 0.8f,
    (0.5f - 0.5f), 0.3f,

    (0.7f - 0.5f), 0.6f, // Face Right
    (0.5f - 0.5f), 0.8f,
    (0.5f - 0.5f), 0.3f,

    (0.3f - 0.5f), 0.4f, // thas the body
    (0.7f - 0.5f), 0.4f,
    (0.5f - 0.5f), -0.3f,

    (0.7f - 0.5f), -0.3f, // Leg down right
    (0.6f - 0.5f), -0.7f,
    (0.5f - 0.5f), -0.3f,

    (0.5f - 0.5f), -0.3f, // Leg down left
    (0.3f - 0.5f), -0.3f,
    (0.4f - 0.5f), -0.7f,

    (0.7f - 0.5f), -0.3f, // Leg up right
    (0.6f - 0.5f), 0.1f,
    (0.5f - 0.5f), -0.3f,

    (0.3f - 0.5f), -0.3f, // Leg up left
    (0.4f - 0.5f), 0.1f,
    (0.5f - 0.5f), -0.3f,

    (0.3f - 0.5f), 0.4f, // Left arm
    (0.4f - 0.5f), 0.4f,
    (0.2f - 0.5f), 0.0f,

    (0.6f - 0.5f), 0.4f, // Right arm
    (0.8f - 0.5f), 0.0f,
    (0.7f - 0.5f), 0.4f,
};

const int m_HumanVertices = 27;
const int m_HumanPrimitiveType = GL_TRIANGLES;


//Animal

// Define our triangle as 3 positions.
float m_Animalattribs[] =
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

int m_AnimalVertices = 40;
int m_AnimalPrimitiveType = GL_LINES;