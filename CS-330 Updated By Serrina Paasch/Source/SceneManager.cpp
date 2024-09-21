///////////////////////////////////////////////////////////////////////////////
// SceneManager.cpp
// ===============
// Manage the generation of 3D objects within the viewport
//
//  AUTHOR: Serrina Paasch
///////////////////////////////////////////////////////////////////////////////
#include "SceneManager.h"

// Constants for repeated values
const glm::vec3 DEFAULT_ROTATION = glm::vec3(0.0f);
const float PLANE_UV_SCALE = 2.0f;
const float DEFAULT_UV_SCALE = 1.0f;
const glm::vec3 FLOOR_SCALE = glm::vec3(20.0f, 2.0f, 10.0f);
const glm::vec3 BACKGROUND_SCALE = glm::vec3(20.0f, 2.0f, 10.0f);
const glm::vec3 TEA_MUG_SCALE = glm::vec3(2.0f, 7.0f, 2.0f);
const glm::vec3 TEA_LIQUID_SCALE = glm::vec3(1.9f, 7.01f, 2.0f);
const glm::vec3 HANDLE_SCALE = glm::vec3(2.0f, 2.5f, 2.0f);

// Helper Functions
void ApplyTransformations(const glm::vec3& scale, float xRotation, float yRotation, float zRotation, const glm::vec3& position) {
    SetTransformations(scale, xRotation, yRotation, zRotation, position);
}

// Time Complexity: O(1) - Constant time to apply transformations
void DrawTexturedMesh(const std::string& texture, const glm::vec3& scale, float xRotation, float yRotation, float zRotation, const glm::vec3& position, const std::string& material = "") {
    ApplyTransformations(scale, xRotation, yRotation, zRotation, position);
    SetShaderTexture(texture);
    SetTextureUVScale(DEFAULT_UV_SCALE, DEFAULT_UV_SCALE);
    if (!material.empty()) {
        SetShaderMaterial(material);
    }
}

// Time Complexity O(1) - Constant time for applying transformations and setting textures
void DrawTexturedMeshWithUVScale(const std::string& texture, const glm::vec3& scale, float xRotation, float yRotation, float zRotation, const glm::vec3& position, float uvScaleX, float uvScaleY, const std::string& material = "") {
    ApplyTransformations(scale, xRotation, yRotation, zRotation, position);
    SetShaderTexture(texture);
    SetTextureUVScale(uvScaleX, uvScaleY);
    if (!material.empty()) {
        SetShaderMaterial(material);
    }
}

// Function to simplify the rendering of repeated objects (Kiss Cone and Plane)
// Time Complexity: 0(1) - Single draw call with UV scaling
void RenderKissObject(const glm::vec3& conePosition, const glm::vec3& planePosition, const std::string& coneTexture, const std::string& planeTexture, const std::string& material) {
    // Kiss Cone Mesh
    DrawTexturedMeshWithUVScale(coneTexture, glm::vec3(0.70f, 1.0f, 1.0f), 0.0f, 0.0f, 0.0f, conePosition, PLANE_UV_SCALE, PLANE_UV_SCALE, material);
    m_basicMeshes->DrawConeMesh(); // Time Complexity: O(1) - Constant time to render cone

    // Kiss Plane Mesh
    DrawTexturedMeshWithUVScale(planeTexture, glm::vec3(0.75f, 1.0f, 0.1f), 90.0f, 90.0f, 0.0f, planePosition, 0.1f, 0.1f);
    m_basicMeshes->DrawPlaneMesh(); // Time Complexity: O(1) - Constant time to render plane
}

/***********************************************************
 *  LoadSceneTextures()
 *
 *  This method loads the textures used in the 3D scene.
 * Time Complexity: O(n) - Linear time where n is the number of textures to load
 ***********************************************************/
void SceneManager::LoadSceneTextures() {
    std::vector<std::pair<std::string, std::string>> textures = {
        {"textures/silver.jpg", "silver"},
        {"textures/tinfoil.jpg", "tinfoil"},
        {"textures/pinkkiss.jpg", "pinkkiss"},
        {"textures/Winnie.jpg", "Winnie"},
        {"textures/floor.jpg", "floor"},
        {"textures/green.jpg", "green"},
        {"textures/lemonlime.jpg", "lemonlime"},
        {"textures/kisstag.jpg", "kisstag"},
        {"textures/wick.jpg", "wick"},
        {"textures/tea.jpg", "tea"},
        {"textures/wax.jpg", "wax"}
    };

    // Time Complexity: O(n) - Iterating through all textures
    for (const auto& texture : textures) {
        CreateGLTexture(texture.first, texture.second); // Time Complexity: O(1) - Creating texture in constant time
    }

    BindGLTextures(); // Time Complexity: O(1) - Binding all textures in constant time
}

/***********************************************************
 *  PrepareScene()
 *
 *  This method prepares the 3D scene by loading textures,
 *  shapes, materials, and setting up lighting.
 * 
 * Time Complexity: O(n) - Linear time where n is the number of meshes loaded
 ***********************************************************/
void SceneManager::PrepareScene() {
    LoadSceneTextures(); // Loading textures
    DefineObjectMaterials(); // Constatnt time for defining material
    SetupSceneLights(); // Constant time for setting up lights

    // Load meshes in memory
    m_basicMeshes->LoadPlaneMesh(); // Time Complexity: O(1) - Loading Individual mesh for each shape
    m_basicMeshes->LoadCylinderMesh();
    m_basicMeshes->LoadConeMesh();
    m_basicMeshes->LoadBoxMesh();
    m_basicMeshes->LoadTorusMesh();
    m_basicMeshes->LoadTaperedCylinderMesh();
}

/***********************************************************
 *  RenderScene()
 *
 *  This method is used for rendering the 3D scene by
 *  transforming and drawing the basic 3D shapes.
 * 
 * Time Complexity: O(T + P), Where T is the number of objects, P is the number of pixels rendered
 ***********************************************************/
void SceneManager::RenderScene() {
    // Floor Mesh
    DrawTexturedMeshWithUVScale("floor", FLOOR_SCALE, 0.0f, 0.0f, 0.0f, glm::vec3(0.0f, 0.0f, 0.0f), PLANE_UV_SCALE, PLANE_UV_SCALE, "wood");
    m_basicMeshes->DrawPlaneMesh();

    // Background Mesh
    DrawTexturedMesh("green", BACKGROUND_SCALE, 90.0f, 0.0f, 0.0f, glm::vec3(0.0f, 10.0f, -7.0f));
    m_basicMeshes->DrawPlaneMesh();

    // Tea Mug Mesh
    DrawTexturedMesh("Winnie", TEA_MUG_SCALE, 0.0f, 50.0f, 0.0f, glm::vec3(7.0f, 0.01f, 1.0f), "glass");
    m_basicMeshes->DrawCylinderMesh();

    // Tea Liquid Mesh
    DrawTexturedMesh("tea", TEA_LIQUID_SCALE, 0.0f, 50.0f, 0.0f, glm::vec3(7.0f, 0.01f, 1.0f), "glass");
    m_basicMeshes->DrawCylinderMesh();

    // Mug Handle Mesh
    DrawTexturedMesh("silver", HANDLE_SCALE, 0.0f, 0.0f, 0.0f, glm::vec3(8.0f, 3.8f, 2.0f), "glass");
    m_basicMeshes->DrawTorusMesh();

    // Laptop Screen Box Mesh
    DrawTexturedMesh("silver", glm::vec3(6.5f, 0.5f, 14.5f), 0.0f, 45.0f, 0.0f, glm::vec3(-9.0f, 0.3f, 2.6f));
    m_basicMeshes->DrawBoxMesh();

    // Render Kiss #1 (Cone and Plane)
    RenderKissObject(glm::vec3(3.0f, 0.01f, 4.0f), glm::vec3(3.0f, 0.9f, 4.0f), "tinfoil", "kisstag", "sunkiss");

    // Render Kiss #2 (Cone and Plane)
    RenderKissObject(glm::vec3(3.0f, 0.01f, 2.0f), glm::vec3(3.0f, 0.9f, 2.0f), "pinkkiss", "kisstag", "sunkiss");

    // Render Kiss #3 (Cone and Plane)
    RenderKissObject(glm::vec3(9.0f, 0.01f, 3.5f), glm::vec3(9.0f, 0.9f, 3.5f), "pinkkiss", "kisstag", "sunkiss");

    // Candle Cylinder Exterior Mesh
    DrawTexturedMesh("wax", glm::vec3(2.0f, 3.5f, 2.0f), 0.0f, 0.0f, 0.0f, glm::vec3(-3.0f, 0.01f, 4.0f), "glass");
    m_basicMeshes->DrawCylinderMesh();

    // Candle Cylinder Interior Mesh
    DrawTexturedMesh("lemonlime", glm::vec3(1.9f, 3.51f, 1.9f), 0.0f, 0.0f, 0.0f, glm::vec3(-3.0f, 0.01f, 4.0f), "glass");
    m_basicMeshes->DrawCylinderMesh();

    // Candlewick Mesh
    DrawTexturedMesh("wick", glm::vec3(0.1f, 0.50f, 0.1f), 0.0f, 0.0f, 0.0f, glm::vec3(-3.0f, 4.0f, 4.0f));
    m_basicMeshes->DrawCylinderMesh();
}
