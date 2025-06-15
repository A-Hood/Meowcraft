#ifndef SKYBOX_H
#define SKYBOX_H

#include <iostream>
#include <vector>
#include <map>

#include "../Shader/Shader.h"
#include "../Camera/Camera.h"

// TODO - Create texture class to easily manage and save textures.
class Skybox {
public:
    Skybox();
    ~Skybox();

public:
    unsigned int InitialiseSkyboxTexture(std::vector<std::string> faces, int skyboxID);
    void InitialiseCubeMap();

    void InitialiseBuffers();

    void RenderSkybox(glm::mat4 view, glm::mat4 projection, Camera& camera);

private:
    unsigned int m_VAO, m_VBO, m_EBO;
    unsigned int m_textureID;
    unsigned int m_cubemapTexture;

    Shader *m_skyboxShader;

    std::string m_skyboxAssetsPath = "../../src/Assets/Skyboxes";

    // Use map to map ids to skybox names
    // TODO - imgui integration for dynamic skybox switching
    std::map<int, std::string> m_skyboxMaps = {
            {1, "Space"},
            {2, "PinkSky"},
    };

    std::vector<std::string> m_faces{
            "right.png",
            "left.png",
            "top.png",
            "bottom.png",
            "front.png",
            "back.png"
    };

    float m_skyboxVertices[108] = {
            -1.0f, 1.0f, -1.0f,
            -1.0f, -1.0f, -1.0f,
            1.0f, -1.0f, -1.0f,
            1.0f, -1.0f, -1.0f,
            1.0f, 1.0f, -1.0f,
            -1.0f, 1.0f, -1.0f,

            -1.0f, -1.0f, 1.0f,
            -1.0f, -1.0f, -1.0f,
            -1.0f, 1.0f, -1.0f,
            -1.0f, 1.0f, -1.0f,
            -1.0f, 1.0f, 1.0f,
            -1.0f, -1.0f, 1.0f,

            1.0f, -1.0f, -1.0f,
            1.0f, -1.0f, 1.0f,
            1.0f, 1.0f, 1.0f,
            1.0f, 1.0f, 1.0f,
            1.0f, 1.0f, -1.0f,
            1.0f, -1.0f, -1.0f,

            -1.0f, -1.0f, 1.0f,
            -1.0f, 1.0f, 1.0f,
            1.0f, 1.0f, 1.0f,
            1.0f, 1.0f, 1.0f,
            1.0f, -1.0f, 1.0f,
            -1.0f, -1.0f, 1.0f,

            -1.0f, 1.0f, -1.0f,
            1.0f, 1.0f, -1.0f,
            1.0f, 1.0f, 1.0f,
            1.0f, 1.0f, 1.0f,
            -1.0f, 1.0f, 1.0f,
            -1.0f, 1.0f, -1.0f,

            -1.0f, -1.0f, -1.0f,
            -1.0f, -1.0f, 1.0f,
            1.0f, -1.0f, -1.0f,
            1.0f, -1.0f, -1.0f,
            -1.0f, -1.0f, 1.0f,
            1.0f, -1.0f, 1.0f
    };
};

#endif //SKYBOX_H