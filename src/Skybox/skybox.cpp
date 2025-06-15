#include "skybox.h"
#include <filesystem>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb_image/stb_image.h>

namespace fs = std::filesystem;

Skybox::Skybox() {
    m_skyboxShader = new Shader("../../src/Assets/Shaders/skyboxPassV.glsl", "../../src/Assets/Shaders/skyboxPassF.glsl");
    InitialiseCubeMap();
    InitialiseBuffers();
    m_skyboxShader->use();
    m_skyboxShader->setInt("skybox", 0);
};

Skybox::~Skybox() {

};

unsigned int Skybox::InitialiseSkyboxTexture(std::vector<std::string> faces, int skyboxID) {
    glGenTextures(1, &m_textureID);
    glBindTexture(GL_TEXTURE_CUBE_MAP, m_textureID);
    std::string path;

    int width, height, nrChannels;
    for (unsigned int i = 0; i < m_faces.size(); i++)
    {
        path = m_skyboxAssetsPath + "/" + m_skyboxMaps[skyboxID] + "/" + m_faces[i];
        std::cout << path << std::endl;
        unsigned char *data = stbi_load(path.c_str(), &width, &height, &nrChannels, 0);
        std::cout << "Gets here 1" << std::endl;
        if (data)
        {
            glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
                         0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data
            );
            std::cout << "Gets here 2" << std::endl;
            stbi_image_free(data);
        }
        else
        {
            std::cout << "Cubemap tex failed to load at path: " << m_faces[i] << std::endl;
            stbi_image_free(data);
        }
    }
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
    return true;
}

void Skybox::InitialiseCubeMap() {
    m_cubemapTexture = InitialiseSkyboxTexture(m_faces, 2);
}

void Skybox::InitialiseBuffers() {
    glGenVertexArrays(1, &m_VAO);
    glGenBuffers(1, &m_VBO);

    glBindVertexArray(m_VAO);
    glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(m_skyboxVertices), &m_skyboxVertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
}

void Skybox::RenderSkybox(glm::mat4 view, glm::mat4 projection, Camera& camera) {
    m_skyboxShader->use();
    view = glm::mat4(glm::mat3(camera.GetViewMatrix())); // remove translation from the view matrix
    m_skyboxShader->setMat4("view", view);
    m_skyboxShader->setMat4("projection", projection);

    glBindVertexArray(m_VAO);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_CUBE_MAP, m_cubemapTexture);
    glDrawArrays(GL_TRIANGLES, 0, 36);
}



