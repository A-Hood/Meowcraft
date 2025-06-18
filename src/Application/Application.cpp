#include "Application.h"
#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

#include "../Chunk/chunk.h"

#include "../ErrorHandling/errorReporting.h"

Application::Application()
{
	Init();
}

void Application::Init()
{
	glfwInit();
	InitWindow();
	InitCamera(); // TODO: add the ability to add more camera

	SetInputMode(m_mouseActive);
}

int Application::InitWindow()
{
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Initialise window
	m_window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "MeowGL", NULL, NULL);
	if (m_window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(m_window);
	glfwSetWindowUserPointer(m_window, this);

	InitCallbacks();
	// Initiliase glad
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}
	glEnable(GL_DEPTH_TEST);
   	return 0;
}

void Application::InitCamera()
{
	m_camera = new Camera(SCREEN_WIDTH, SCREEN_HEIGHT);
}

void Application::InitCallbacks()
{
	glfwSetFramebufferSizeCallback(m_window, [](GLFWwindow* window, auto width, auto height) {
		auto app = reinterpret_cast<Application*>(glfwGetWindowUserPointer(window));
		glViewport(0, 0, width, height);
		});
    glfwSetCursorPosCallback(m_window, [](GLFWwindow* window, double xpos, double ypos) {
        auto app = reinterpret_cast<Application*>(glfwGetWindowUserPointer(window));
        app->MouseInputFunc(window, xpos, ypos);
    });
	glfwSetScrollCallback(m_window, [](GLFWwindow* window, double xoffset, double yoffset) {
		auto app = reinterpret_cast<Application*>(glfwGetWindowUserPointer(window));
		app->ScrollInputFunc(window, xoffset, yoffset);
		});
}

void Application::SetInputMode(bool active)
{
    // if mouse currently is active - disable mouse
    if(active)
    {
        glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
        m_mouseActive = !m_mouseActive;
        m_camera->SetMouseActiveBool(m_mouseActive);
        std::cout << "Disabled cursor" << std::endl;
        return;
    }
    // if mouse is not currently active - enable mouse
    glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    m_mouseActive = !m_mouseActive;
    m_camera->SetMouseActiveBool(m_mouseActive);
    std::cout << "Activated cursor" << std::endl;
}

int Application::Run()
{
    enableReportGlErrors();

    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

    // Setup Platform/Renderer backends
    ImGui_ImplGlfw_InitForOpenGL(m_window, true);          // Second param install_callback=true will install GLFW callbacks and chain to existing ones.
    ImGui_ImplOpenGL3_Init();

	Shader shader("../../src/Assets/Shaders/v.glsl", "../../src/Assets/Shaders/f.glsl");
    Skybox* skybox = new Skybox();

    Chunk chunk;

    // Wireframe
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    // render loop
	while (!glfwWindowShouldClose(m_window))
	{
            // Delta time
            float currentFrame = glfwGetTime();
            m_deltaTime = currentFrame - m_lastFrame;
            m_lastFrame = currentFrame;

            // input
            ProcessInput(m_camera);

            // render
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            // Apply shader and set uniforms
            shader.use();
            glm::mat4 model = glm::mat4(1.0f);
            glm::mat4 view = m_camera->GetViewMatrix();
            glm::mat4 projection = glm::perspective(glm::radians(m_camera->GetFOV()), (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT, 0.1f, 100.0f);
            shader.setMat4("model", model);
            shader.setMat4("view", view);
            shader.setMat4("projection", projection);
            shader.setVec3("viewPos", m_camera->GetCameraPos().x, m_camera->GetCameraPos().y, m_camera->GetCameraPos().z);

            // Render chunk
            chunk.Render();

            // Skybox rendering
            /*
            glDepthFunc(GL_LEQUAL);
            skybox->RenderSkybox(view, projection, *m_camera);
            glDepthFunc(GL_LESS);
            glBindVertexArray(0);
            */
            SwapBuffers(m_window);
            glfwPollEvents();
	}

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
	glfwTerminate();
	return 0;
}

void Application::SwapBuffers(GLFWwindow *window)
{
    ImGui::EndFrame();
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    glfwSwapBuffers(window);

    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
    //ImGui::ShowDemoWindow();
}

void Application::FramebufferSizeCallback(GLFWwindow* window, int width, int height)
{
	// make sure the viewport matches the new window dimensions; note that width and 
	// height will be significantly larger than specified on retina displays.
	glViewport(0, 0, width, height);
}

void Application::MouseInputFunc(GLFWwindow* window, double xpos, double ypos)
{
	m_camera->MouseInput(m_deltaTime, xpos, ypos);
}

 void Application::ScrollInputFunc(GLFWwindow* window, double xoffset, double yoffset)
{
	m_camera->MouseScrollInput(xoffset, yoffset);
}

 void Application::ProcessInput(Camera* camera)
 {
	 if (glfwGetKey(m_window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		 glfwSetWindowShouldClose(m_window, true);

     if ((glfwGetKey(m_window, GLFW_KEY_F1) == GLFW_PRESS) && !m_mouseActivateButtonPreviouslyPressed)
         SetInputMode(m_mouseActive);

     if (!m_mouseActive)
	    camera->ProcessInput(m_window, m_deltaTime);

     m_mouseActivateButtonPreviouslyPressed = glfwGetKey(m_window, GLFW_KEY_F1);
 }