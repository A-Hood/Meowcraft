#ifndef CAMERA_H
#define CAMERA_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Camera
{
public:
	Camera(unsigned int screenHeight, unsigned int screenWidth);
	~Camera();

	glm::vec3 GetCameraPos() {
		return m_CameraPos;
	}

    void SetMouseActiveBool(const bool value) { m_mouseActive = value; }

public:
	glm::mat4 UpdateView(float deltaTime);
	glm::mat4 UpdatePerspective();

	void ProcessInput(GLFWwindow* window, float deltaTime);
	void MouseInput(float deltaTime, double xpos, double ypos);
	void MouseScrollInput(double xoffset, double yoffset);

    glm::mat4 GetViewMatrix() {
        return glm::lookAt(m_CameraPos, m_CameraPos + m_CameraFront, m_CameraUp);
    }

    float GetFOV() {
        return m_FOV;
    }
private:
	int m_ScreenWidth;
	int m_ScreenHeight;

	glm::vec3 m_CameraPos = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::vec3 m_CameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
	glm::vec3 m_CameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

	bool m_FirstMouse = true;
	float m_Yaw = -90.0f;
	float m_Pitch = 0.0f;
	float m_LastX;
	float m_LastY;
	float m_FOV = 45.0f;

    bool m_mouseActive = false;
};
#endif