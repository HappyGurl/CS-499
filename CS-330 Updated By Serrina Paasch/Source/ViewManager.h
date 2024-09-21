///////////////////////////////////////////////////////////////////////////////
// ViewManager.h
// ============
// Manages the viewing of 3D objects within the viewport
//
// AUTHOR: Serrina Paasch
///////////////////////////////////////////////////////////////////////////////

#pragma once

#include "ShaderManager.h"
#include "Camera.h"

// GLFW library
#include "GLFW/glfw3.h" 

class ViewManager
{
public:
    // Constructor
    ViewManager(ShaderManager* pShaderManager);

    // Destructor
    ~ViewManager();

    // Mouse position callback for interaction with the 3D scene
    static void MousePositionCallback(GLFWwindow* window, double xMousePos, double yMousePos);

    // Create the initial OpenGL display window
    GLFWwindow* CreateDisplayWindow(const char* windowTitle);

    // Prepare the conversion from 3D object display to 2D scene display
    void PrepareSceneView();

private:
    // Pointer to ShaderManager object
    ShaderManager* m_pShaderManager;

    // Active OpenGL display window
    GLFWwindow* m_pWindow;

    // Process keyboard events for interaction with the 3D scene
    void ProcessKeyboardEvents();
};
