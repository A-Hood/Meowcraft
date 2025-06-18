#ifndef CHUNK_H
#define CHUNK_H

#include "../Block/block.h"
#include "../Shader/Shader.h"
#include <glm/gtc/matrix_transform.hpp>
#include <vector>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

const int CHUNK_WIDTH = 16;

class Chunk {
public:
    Chunk();

    void InitChunk();
    void BuildMesh();
    void InitBuffers();
    void InitShaders();

    void Render();
private:
    std::vector<Block*> mBlocksInChunk;
    //std::vector<glm::vec3> mChunkVertices;
    std::vector<glm::vec3> mChunkVertices;

    Shader* mShader;

    unsigned int mVAO, mVBO;
};


#endif
