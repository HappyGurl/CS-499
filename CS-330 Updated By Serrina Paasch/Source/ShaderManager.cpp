///////////////////////////////////////////////////////////////////////////////
// ShaderManager.cpp
// =================
// Manage the creation, compilation, and linking of shader programs
//
// AUTHOR: Serrina Paasch
///////////////////////////////////////////////////////////////////////////////

#include "ShaderManager.h"
#include <iostream>
#include <fstream>
#include <sstream>

// Constructor: Initialize member variables
ShaderManager::ShaderManager()
{
    m_shaderProgram = 0;
}

// Destructor: Cleanup the shader program
ShaderManager::~ShaderManager()
{
    if (m_shaderProgram != 0)
    {
        glDeleteProgram(m_shaderProgram);
        m_shaderProgram = 0;
    }
}

/***********************************************************
 *  LoadShaders()
 *
 *  This method loads and compiles vertex and fragment shaders
 *  from provided file paths and links them into a shader program.
 ***********************************************************/
bool ShaderManager::LoadShaders(const char* vertexPath, const char* fragmentPath)
{
    // 1. Retrieve the vertex and fragment shader source code from filePath
    std::string vertexCode;
    std::string fragmentCode;
    std::ifstream vShaderFile;
    std::ifstream fShaderFile;

    // Ensure ifstream objects can throw exceptions
    vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

    try
    {
        // Open files
        vShaderFile.open(vertexPath);
        fShaderFile.open(fragmentPath);
        std::stringstream vShaderStream, fShaderStream;

        // Read file's buffer contents into streams
        vShaderStream << vShaderFile.rdbuf();
        fShaderStream << fShaderFile.rdbuf();

        // Close file handlers
        vShaderFile.close();
        fShaderFile.close();

        // Convert stream into string
        vertexCode = vShaderStream.str();
        fragmentCode = fShaderStream.str();
    }
    catch (std::ifstream::failure& e)
    {
        std::cerr << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ: " << e.what() << std::endl;
        return false;
    }

    const char* vShaderCode = vertexCode.c_str();
    const char* fShaderCode = fragmentCode.c_str();

    // 2. Compile shaders
    unsigned int vertex, fragment;
    int success;
    char infoLog[512];

    // Vertex Shader
    vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &vShaderCode, NULL);
    glCompileShader(vertex);

    // Print compile errors if any
    glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertex, 512, NULL, infoLog);
        std::cerr << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
        return false;
    }

    // Fragment Shader
    fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &fShaderCode, NULL);
    glCompileShader(fragment);

    // Print compile errors if any
    glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragment, 512, NULL, infoLog);
        std::cerr << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
        return false;
    }

    // Shader Program
    m_shaderProgram = glCreateProgram();
    glAttachShader(m_shaderProgram, vertex);
    glAttachShader(m_shaderProgram, fragment);
    glLinkProgram(m_shaderProgram);

    // Print linking errors if any
    glGetProgramiv(m_shaderProgram, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(m_shaderProgram, 512, NULL, infoLog);
        std::cerr << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
        return false;
    }

    // Delete the shaders as they're linked into our program now and no longer needed
    glDeleteShader(vertex);
    glDeleteShader(fragment);

    return true;
}

/***********************************************************
 *  UseProgram()
 *
 *  Use the compiled shader program.
 ***********************************************************/
void ShaderManager::UseProgram()
{
    if (m_shaderProgram != 0)
    {
        glUseProgram(m_shaderProgram);
    }
}

/***********************************************************
 *  setMat4Value()
 *
 *  Set a 4x4 matrix uniform in the shader.
 ***********************************************************/
void ShaderManager::setMat4Value(const std::string& name, const glm::mat4& mat) const
{
    glUniformMatrix4fv(glGetUniformLocation(m_shaderProgram, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}

/***********************************************************
 *  setVec3Value()
 *
 *  Set a vec3 uniform in the shader.
 ***********************************************************/
void ShaderManager::setVec3Value(const std::string& name, const glm::vec3& value) const
{
    glUniform3fv(glGetUniformLocation(m_shaderProgram, name.c_str()), 1, &value[0]);
}
