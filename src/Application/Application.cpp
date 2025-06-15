#include "Application.h"

Application::Application()
{
	Init();
}

Application::~Application()
{
}

void Application::Init()
{
	glfwInit();
	InitWindow();
	InitCamera(); // TODO: add the ability to add more camera

	SetInputMode();
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

void Application::SetInputMode()
{
	glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

int Application::Run()
{
	//Shader ourShader("C:/Users/dabpo/Documents/GitHub/Meowcraft/src/Assets/Shaders/v.glsl", "C:/Users/dabpo/Documents/GitHub/Meowcraft/src/Assets/Shaders/f.glsl");
	Shader shader("../../src/Assets/Shaders/v.glsl", "../../src/Assets/Shaders/f.glsl");

    Skybox* skybox = new Skybox();

    float cubeVertices[] = {
            // positions          // texture Coords
            -0.5f, -0.5f, -0.5f, 0.0f, 0.0f,
            0.5f, -0.5f, -0.5f, 1.0f, 0.0f,
            0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
            0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
            -0.5f, 0.5f, -0.5f, 0.0f, 1.0f,
            -0.5f, -0.5f, -0.5f, 0.0f, 0.0f,

            -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
            0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
            0.5f, 0.5f, 0.5f, 1.0f, 1.0f,
            0.5f, 0.5f, 0.5f, 1.0f, 1.0f,
            -0.5f, 0.5f, 0.5f, 0.0f, 1.0f,
            -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,

            -0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
            -0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
            -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
            -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
            -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
            -0.5f, 0.5f, 0.5f, 1.0f, 0.0f,

            0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
            0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
            0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
            0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
            0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
            0.5f, 0.5f, 0.5f, 1.0f, 0.0f,

            -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
            0.5f, -0.5f, -0.5f, 1.0f, 1.0f,
            0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
            0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
            -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
            -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,

            -0.5f, 0.5f, -0.5f, 0.0f, 1.0f,
            0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
            0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
            0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
            -0.5f, 0.5f, 0.5f, 0.0f, 0.0f,
            -0.5f, 0.5f, -0.5f, 0.0f, 1.0f
    };

    unsigned int cubeVAO, cubeVBO;
    glGenVertexArrays(1, &cubeVAO);
    glGenBuffers(1, &cubeVBO);
    glBindVertexArray(cubeVAO);
    glBindBuffer(GL_ARRAY_BUFFER, cubeVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVertices), &cubeVertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));

    unsigned int cubeTexture;
    glGenTextures(1, &cubeTexture);
    int width, height, nrComponents;
    unsigned char *data = stbi_load("C:/Users/dabpo/Documents/GitHub/Meowcraft/src/Assets/Textures/container.jpg", &width, &height, &nrComponents, 0);
    if (data)
    {
        GLenum format;
        if (nrComponents == 1)
            format = GL_RED;
        else if (nrComponents == 3)
            format = GL_RGB;
        else if (nrComponents == 4)
            format = GL_RGBA;

            glBindTexture(GL_TEXTURE_2D, cubeTexture);
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        stbi_image_free(data);
    }
    else
    {
        std::cout << "Texture failed to load at path: " << "C:/Users/dabpo/Documents/GitHub/Meowcraft/src/Assets/Textures/container.jpg" << std::endl;
        stbi_image_free(data);
    }
    
    shader.use();
    shader.setInt("texture1",0);

	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	// render loop
	while (!glfwWindowShouldClose(m_window))
	{
		// Delta time
		float currentFrame = glfwGetTime();
		m_deltaTime = currentFrame - m_lastFrame;
		m_lastFrame = currentFrame;

		// input
		// -----
		ProcessInput(m_camera);

		// render
		// ------
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        shader.use();
        glm::mat4 model = glm::mat4(1.0f);
        glm::mat4 view = m_camera->GetViewMatrix();
        glm::mat4 projection = glm::perspective(glm::radians(m_camera->GetFOV()), (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT, 0.1f, 100.0f);
        shader.setMat4("model", model);
        shader.setMat4("view", view);
        shader.setMat4("projection", projection);

        // cubes
        glBindVertexArray(cubeVAO);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, cubeTexture);
        glDrawArrays(GL_TRIANGLES, 0, 36);
        glBindVertexArray(0);


        glDepthFunc(GL_LEQUAL);
        skybox->RenderSkybox(view, projection, *m_camera);
        glDepthFunc(GL_LESS);
        glBindVertexArray(0);

		glfwSwapBuffers(m_window);
		glfwPollEvents();
	}

	//DeleteBuffers();
	glfwTerminate();
	return 0;
}

void Application::Update()
{
	// run update on input and stuff here
}

/*
void Application::Render()
{
	for (unsigned int i = 0; i < m_renderQueue.size(); ++i) {
		m_renderQueue[i].Draw();
	}
}

void Application::DeleteBuffers()
{
	for (unsigned int i = 0; i < m_renderQueue.size(); ++i) {
		m_renderQueue[i].DeleteBuffers();
	}
}
*/

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

	 camera->ProcessInput(m_window, m_deltaTime);
 }