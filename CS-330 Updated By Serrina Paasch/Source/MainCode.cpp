///////////////////////////////////////////////////////////////////////////////
// MainCode.cpp
// ===============
// setup the viewing of 3D objects within the viewport
//
//  AUTHOR: Serrina Paasch
///////////////////////////////////////////////////////////////////////////////

#include <iostream>         // error handling and output
#include <cstdlib>          // EXIT_FAILURE

#include <GL/glew.h>        // GLEW library
#include "GLFW/glfw3.h"     // GLFW library

// GLM Math Header inclusions
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "SceneManager.h"
#include "ViewManager.h"
#include "ShapeMeshes.h"
#include "ShaderManager.h"

// Namespace for declaring global variables
namespace
{
	// Macro for window title
	const char* const WINDOW_TITLE = "7-1 Final Project and Milestones";

	// Main GLFW window
	GLFWwindow* g_Window = nullptr;

	// scene manager object for managing the 3D scene prepare and render
	SceneManager* g_SceneManager = nullptr;
	// shader manager object for dynamic interaction with the shader code
	ShaderManager* g_ShaderManager = nullptr;
	// view manager object for managing the 3D view setup and projection to 2D
	ViewManager* g_ViewManager = nullptr;
}

// Function declarations - all functions that are called manually
// need to be pre-declared at the beginning of the source code.
bool InitializeGLFW();
bool InitializeGLEW();


/***********************************************************
 *  main(int, char*)
 *
 *  This function gets called after the application has been
 *  launched.
 ***********************************************************/
int main(int argc, char* argv[])
{
	// if GLFW fails initialization, then terminate the application
	if (!InitializeGLFW())
	{
		return(EXIT_FAILURE);
	}

	// Create Shader Manager
	g_ShaderManager = new ShaderManager();

	// Initialize the ViewManager with the ShaderManager
	g_ViewManager = new ViewManager(g_ShaderManager);

	// Create the display window
	g_Window = g_ViewManager->CreateDisplayWindow(WINDOW_TITLE);

	// if GLEW fails initialization, then terminate the application
	if (!InitializeGLEW())
	{
		return(EXIT_FAILURE);
	}

	// Load shaders from external GLSL files
	g_ShaderManager->LoadShaders(
		"../../../Utilities/shaders/vertexShader.glsl",
		"../../../Utilities/shaders/fragmentShader.glsl");
	g_ShaderManager->use();

	// Initialize Scene Manager and prepare the 3D scene
	g_SceneManager = new SceneManager(g_ShaderManager);
	g_SceneManager->PrepareScene();

	// Main application loop
	while (!glfwWindowShouldClose(g_Window))
	{
		// Enable z-depth
		glEnable(GL_DEPTH_TEST);

		// Clear the frame and z buffers
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Prepare the 3D scene view projection
		g_ViewManager->PrepareSceneView();

		// Render the scene with updated objects and textures
		g_SceneManager->RenderScene();

		// Swap the buffers
		glfwSwapBuffers(g_Window);

		// Poll events
		glfwPollEvents();
	}

	// Cleanup and free memory
	if (g_SceneManager != nullptr)
	{
		delete g_SceneManager;
		g_SceneManager = nullptr;
	}
	if (g_ViewManager != nullptr)
	{
		delete g_ViewManager;
		g_ViewManager = nullptr;
	}
	if (g_ShaderManager != nullptr)
	{
		delete g_ShaderManager;
		g_ShaderManager = nullptr;
	}

	// Terminate GLFW
	glfwTerminate();

	// Exit the program successfully
	return EXIT_SUCCESS;
}

/***********************************************************
 *	InitializeGLFW()
 *
 *  This function is used to initialize the GLFW library.
 ***********************************************************/
bool InitializeGLFW()
{
	// GLFW: initialize and configure
	glfwInit();

#ifdef __APPLE__
	// Set OpenGL version for Mac compatibility
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#else
	// Set OpenGL version for other platforms
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#endif

	return true;
}

/***********************************************************
 *	InitializeGLEW()
 *
 *  This function is used to initialize the GLEW library.
 ***********************************************************/
bool InitializeGLEW()
{
	// GLEW: initialize
	GLenum GLEWInitResult = glewInit();
	if (GLEW_OK != GLEWInitResult)
	{
		std::cerr << glewGetErrorString(GLEWInitResult) << std::endl;
		return false;
	}

	// Output OpenGL version info
	std::cout << "INFO: OpenGL Successfully Initialized\n";
	std::cout << "INFO: OpenGL Version: " << glGetString(GL_VERSION) << "\n" << std::endl;

	return true;
}
