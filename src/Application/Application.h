#ifndef APPLICATION_H
#define APPLICATION_H

#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>
#include <math.h>
#include <stb_image/stb_image.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

#include "../Camera/Camera.h"
#include "../Shader/Shader.h"
#include "../Skybox/Skybox.h"

const int SCREEN_WIDTH = 1920;
const int SCREEN_HEIGHT = 1080;

class Application
{
public:
	Application();
	
	void Init();
	int InitWindow();
	void InitCamera();
	void InitCallbacks();

    void InitImGui();

	void SetInputMode(bool active); // just make it cursor for now
	void ProcessInput(Camera* camera);

	int Run();

	void Update();
	void Render();

	void SwapBuffers(GLFWwindow *window, bool* p_open);

private:
	void FramebufferSizeCallback(GLFWwindow* window, int width, int height);
	void MouseInputFunc(GLFWwindow* window, double xpos, double ypos);
	void ScrollInputFunc(GLFWwindow* window, double xoffset, double yoffset);


private:
	GLFWwindow* m_window;
	Camera* m_camera;

    ImGuiIO mIO;
    ImGuiWindowFlags window_flags;

    float m_deltaTime = 0.0f;	// Time between current frame and last frame
    float m_lastFrame = 0.0f; // Time of last frame

    bool m_mouseActive = true;
    bool m_mouseActivateButtonPreviouslyPressed = false;
};

#endif

