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
	Shader lightingShader("../../src/Assets/Shaders/v.glsl", "../../src/Assets/Shaders/f.glsl");
    Shader lightCubeShader("../../src/Assets/Shaders/v.glsl", "../../src/Assets/Shaders/lightCubeF.glsl");
    Skybox* skybox = new Skybox();

    // TODO - Package all vertex information into structs to make my stuff a bit more manageable
    float cubeVertices[] = {
            // vertex             // tex       // normals
            -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,  0.0f, 0.0f, -1.0f,
            0.5f, -0.5f, -0.5f,   1.0f, 0.0f,  0.0f, 0.0f, -1.0f,
            0.5f, 0.5f, -0.5f,    1.0f, 1.0f,  0.0f, 0.0f, -1.0f,
            0.5f, 0.5f, -0.5f,    1.0f, 1.0f,  0.0f, 0.0f, -1.0f,
            -0.5f, 0.5f, -0.5f,   0.0f, 1.0f,  0.0f, 0.0f, -1.0f,
            -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,  0.0f, 0.0f, -1.0f,

            -0.5f, -0.5f, 0.5f,   0.0f, 0.0f,  0.0f, 0.0f, 1.0f,
            0.5f, -0.5f, 0.5f,    1.0f, 0.0f,  0.0f, 0.0f, 1.0f,
            0.5f, 0.5f, 0.5f,     1.0f, 1.0f,  0.0f, 0.0f, 1.0f,
            0.5f, 0.5f, 0.5f,     1.0f, 1.0f,  0.0f, 0.0f, 1.0f,
            -0.5f, 0.5f, 0.5f,    0.0f, 1.0f,  0.0f, 0.0f, 1.0f,
            -0.5f, -0.5f, 0.5f,   0.0f, 0.0f,  0.0f, 0.0f, 1.0f,

            -0.5f, 0.5f, 0.5f,    1.0f, 0.0f,  -1.0f, 0.0f, 0.0f,
            -0.5f, 0.5f, -0.5f,   1.0f, 1.0f,  -1.0f, 0.0f, 0.0f,
            -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,  -1.0f, 0.0f, 0.0f,
            -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,  -1.0f, 0.0f, 0.0f,
            -0.5f, -0.5f, 0.5f,   0.0f, 0.0f,  -1.0f, 0.0f, 0.0f,
            -0.5f, 0.5f, 0.5f,    1.0f, 0.0f,  -1.0f, 0.0f, 0.0f,

            0.5f, 0.5f, 0.5f,     1.0f, 0.0f,  1.0f, 0.0f, 0.0f,
            0.5f, 0.5f, -0.5f,    1.0f, 1.0f,  1.0f, 0.0f, 0.0f,
            0.5f, -0.5f, -0.5f,   0.0f, 1.0f,  1.0f, 0.0f, 0.0f,
            0.5f, -0.5f, -0.5f,   0.0f, 1.0f,  1.0f, 0.0f, 0.0f,
            0.5f, -0.5f, 0.5f,    0.0f, 0.0f,  1.0f, 0.0f, 0.0f,
            0.5f, 0.5f, 0.5f,     1.0f, 0.0f,  1.0f, 0.0f, 0.0f,

            -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,  0.0f, -1.0f, 0.0f,
            0.5f, -0.5f, -0.5f,   1.0f, 1.0f,  0.0f, -1.0f, 0.0f,
            0.5f, -0.5f, 0.5f,    1.0f, 0.0f,  0.0f, -1.0f, 0.0f,
            0.5f, -0.5f, 0.5f,    1.0f, 0.0f,  0.0f, -1.0f, 0.0f,
            -0.5f, -0.5f, 0.5f,   0.0f, 0.0f,  0.0f, -1.0f, 0.0f,
            -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,  0.0f, -1.0f, 0.0f,

            -0.5f, 0.5f, -0.5f,   0.0f, 1.0f,  0.0f, 1.0f, 0.0f,
            0.5f, 0.5f, -0.5f,    1.0f, 1.0f,  0.0f, 1.0f, 0.0f,
            0.5f, 0.5f, 0.5f,     1.0f, 0.0f,  0.0f, 1.0f, 0.0f,
            0.5f, 0.5f, 0.5f,     1.0f, 0.0f,  0.0f, 1.0f, 0.0f,
            -0.5f, 0.5f, 0.5f,    0.0f, 0.0f,  0.0f, 1.0f, 0.0f,
            -0.5f, 0.5f, -0.5f,   0.0f, 1.0f,  0.0f, 1.0f, 0.0f
    };

    unsigned int cubeVAO, cubeVBO;
    glGenVertexArrays(1, &cubeVAO);
    glGenBuffers(1, &cubeVBO);
    glBindVertexArray(cubeVAO);
    glBindBuffer(GL_ARRAY_BUFFER, cubeVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVertices), &cubeVertices, GL_STATIC_DRAW);
    // Vertexes
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    /*
    // Tex Coords
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    */
    // Normals
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(5 * sizeof(float)));
    glEnableVertexAttribArray(1);


    unsigned int lightCubeVAO;
    glGenVertexArrays(1, &lightCubeVAO);
    glBindVertexArray(lightCubeVAO);
    // we only need to bind to the VBO, the container's VBO's data already contains the data.
    glBindBuffer(GL_ARRAY_BUFFER, cubeVBO);
    // set the vertex attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

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

    // don't forget to use the corresponding shader program first (to set the uniform)
    lightingShader.use();
    lightingShader.setVec3("objectColor", 1.0f, 0.5f, 0.31f);
    lightingShader.setVec3("lightColor",  1.0f, 1.0f, 1.0f);

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

            glm::vec3 lightPos(1.5f, 0.0f, 1.0f);
            lightPos.x = sin(glfwGetTime() / 2.0f) * 2.0f;

            lightingShader.use();
            glm::mat4 model = glm::mat4(1.0f);
            glm::mat4 view = m_camera->GetViewMatrix();
            glm::mat4 projection = glm::perspective(glm::radians(m_camera->GetFOV()), (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT, 0.1f, 100.0f);
            //model = glm::rotate(model, (float)glfwGetTime() * glm::radians(50.0f), glm::vec3(0.5f, 1.0f, 0.0f));
            lightingShader.setMat4("model", model);
            lightingShader.setMat4("view", view);
            lightingShader.setMat4("projection", projection);
            lightingShader.setVec3("lightPos", lightPos.x, lightPos.y, lightPos.z);
            lightingShader.setVec3("viewPos", m_camera->GetCameraPos().x, m_camera->GetCameraPos().y, m_camera->GetCameraPos().z);

            // cubes
            glBindVertexArray(cubeVAO);
            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, cubeTexture);
            glDrawArrays(GL_TRIANGLES, 0, 36);
            glBindVertexArray(0);

            // light cube
            lightCubeShader.use();
            model = glm::mat4(1.0f);
            model = glm::translate(model, lightPos);
            //model = glm::rotate(model, (float)glfwGetTime(), glm::vec3(0.0f, 1.0f, 0.0f));
            model = glm::scale(model, glm::vec3(0.2f));
            lightCubeShader.setMat4("model", model);
            lightCubeShader.setMat4("view", view);
            lightCubeShader.setMat4("projection", projection);
            glBindVertexArray(lightCubeVAO);
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