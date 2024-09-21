///////////////////////////////////////////////////////////////////////////////
// ShapeMeshes.cpp
// ===============
// Manage the creation and rendering of different 3D shape meshes
//
// AUTHOR: Serrina Paasch
///////////////////////////////////////////////////////////////////////////////

#include "ShapeMeshes.h"
#include <iostream>
#include <glad/glad.h>

// Constructor: Initialize member variables
ShapeMeshes::ShapeMeshes()
{
    m_VAO = 0;
    m_VBO = 0;
    m_EBO = 0;
}

// Destructor: Cleanup the mesh data
ShapeMeshes::~ShapeMeshes()
{
    if (m_VAO != 0)
    {
        glDeleteVertexArrays(1, &m_VAO);
        m_VAO = 0;
    }
    if (m_VBO != 0)
    {
        glDeleteBuffers(1, &m_VBO);
        m_VBO = 0;
    }
    if (m_EBO != 0)
    {
        glDeleteBuffers(1, &m_EBO);
        m_EBO = 0;
    }
}

/***********************************************************
 *  CreateCube()
 *
 *  This method generates and stores the vertex data for a cube.
 ***********************************************************/
void ShapeMeshes::CreateCube()
{
    // Define vertices and indices for a cube
    float vertices[] = {
        // Positions          // Normals           // Texture Coords
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,
         0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  0.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  1.0f,
        // Other faces...
    };
    unsigned int indices[] = {
        0, 1, 2, 2, 3, 0, // Back face
        // Other face indices...
    };

    // Generate and bind VAO, VBO, EBO
    glGenVertexArrays(1, &m_VAO);
    glGenBuffers(1, &m_VBO);
    glGenBuffers(1, &m_EBO);

    glBindVertexArray(m_VAO);

    // Bind and set vertex buffer
    glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // Bind and set index buffer
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // Define the vertex attribute layout (position, normals, texture coords)
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    glBindVertexArray(0); // Unbind VAO
}

/***********************************************************
 *  CreateSphere()
 *
 *  This method generates and stores the vertex data for a sphere.
 ***********************************************************/
void ShapeMeshes::CreateSphere()
{
    // Implementation of sphere generation using appropriate algorithm (e.g., UV sphere)
    // Similar setup to CreateCube() but different vertex data
}

/***********************************************************
 *  RenderMesh()
 *
 *  Renders the currently stored shape mesh.
 ***********************************************************/
void ShapeMeshes::RenderMesh()
{
    if (m_VAO != 0)
    {
        glBindVertexArray(m_VAO);
        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0); // 36 is for a cube; adjust accordingly for other shapes
        glBindVertexArray(0);
    }
}
