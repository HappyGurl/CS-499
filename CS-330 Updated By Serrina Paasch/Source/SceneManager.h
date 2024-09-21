///////////////////////////////////////////////////////////////////////////////
// SceneManager.h
// ==============
// Manage the loading and rendering of 3D scenes
//
// AUTHOR: Serrina Paasch
///////////////////////////////////////////////////////////////////////////////

#pragma once

#include "ShaderManager.h"
#include "ShapeMeshes.h"

#include <string>
#include <vector>
#include <glm/glm.hpp>

/***********************************************************
 *  SceneManager
 *
 *  This class contains the code for preparing and rendering
 *  3D scenes, including the shader settings.
 ***********************************************************/
class SceneManager
{
public:
    // Constructor: Takes in a pointer to a ShaderManager object
    SceneManager(ShaderManager* pShaderManager);

    // Destructor: Cleans up any allocated resources
    ~SceneManager();

    // Structure to hold information about loaded textures
    struct TEXTURE_INFO
    {
        std::string tag;
        uint32_t ID;
    };

    // Structure to hold material properties for objects
    struct OBJECT_MATERIAL
    {
        float ambientStrength;
        glm::vec3 ambientColor;
        glm::vec3 diffuseColor;
        glm::vec3 specularColor;
        float shininess;
        std::string tag;
    };

private:
    ShaderManager* m_pShaderManager;     // Pointer to shader manager object
    ShapeMeshes* m_basicMeshes;          // Pointer to basic shapes object
    int m_loadedTextures;                // Total number of loaded textures
    TEXTURE_INFO m_textureIDs[16];       // Array to hold loaded texture info
    std::vector<OBJECT_MATERIAL> m_objectMaterials; // List of defined object materials

    // Load texture images and convert them to OpenGL texture data
    bool CreateGLTexture(const char* filename, std::string tag);

    // Bind loaded OpenGL textures to memory slots
    void BindGLTextures();

    // Free the loaded OpenGL textures
    void DestroyGLTextures();

    // Find a loaded texture by tag
    int FindTextureID(std::string tag);

    // Find the slot for a loaded texture by tag
    int FindTextureSlot(std::string tag);

    // Find a defined material by tag
    bool FindMaterial(std::string tag, OBJECT_MATERIAL& material);

    // Set transformation values into the transformation buffer
    void SetTransformations(
        glm::vec3 scaleXYZ,
        float XrotationDegrees,
        float YrotationDegrees,
        float ZrotationDegrees,
        glm::vec3 positionXYZ);

    // Set the color values in the shader
    void SetShaderColor(
        float redColorValue,
        float greenColorValue,
        float blueColorValue,
        float alphaValue);

    // Set the texture data into the shader
    void SetShaderTexture(
        std::string textureTag);

    // Set the UV scale for texture mapping
    void SetTextureUVScale(
        float u, float v);

    // Set the object material data into the shader
    void SetShaderMaterial(
        std::string materialTag);

public:
    // Prepare the scene: Create objects, textures, and materials
    void PrepareScene();

    // Render the scene: Draw objects using shaders and materials
    void RenderScene();

    // Load all required textures for the scene
    void LoadSceneTextures();

    // Define all object materials for the scene
    void DefineObjectMaterials();

    // Set up and define light sources for the scene
    void SetupSceneLights();
};
