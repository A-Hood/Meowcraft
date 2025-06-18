#ifndef CHUNK_H
#define CHUNK_H

#include "../Block/block.h"
#include "../Shader/Shader.h"
#include <glm/gtc/matrix_transform.hpp>
#include <vector>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

const int CHUNK_SIZE = 16;
const int CHUNK_AREA = CHUNK_SIZE * CHUNK_SIZE;
const int CHUNK_VOLUME = CHUNK_SIZE * CHUNK_SIZE * CHUNK_SIZE;

// to create chunk, loop through

class Chunk {
public:
    Chunk();

    void InitChunk();
    void BuildMesh();
    void InitBuffers();
    void InitShaders();

    int GetIndex(int x, int y, int z) {
        return y * CHUNK_AREA + z * CHUNK_SIZE + x;
    }

    bool ShouldAddFace(const std::array<float, 18> &face, const glm::vec3 &position);
    int GetIndex(const glm::vec3 &position);
    void AddFace(const std::array<float, 18> &face, const glm::vec3 &position);
    void Render();
private:
    std::vector<Block*> mBlocksInChunk;
    std::vector<glm::vec3> mChunkVertices;

    Shader* mShader;

    unsigned int mVAO, mVBO;
};


#endif
