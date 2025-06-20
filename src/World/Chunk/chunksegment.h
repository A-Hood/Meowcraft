#ifndef CHUNKSEGMENT_H
#define CHUNKSEGMENT_H

#include "../Block/block.h"
#include "../../Shader/Shader.h"
#include "glm/gtc/matrix_transform.hpp"
#include <vector>

#include "glad/glad.h"
#include "GLFW/glfw3.h"

const int CHUNK_SIZE = 16;
const int CHUNK_AREA = CHUNK_SIZE * CHUNK_SIZE;
const int CHUNK_VOLUME = CHUNK_SIZE * CHUNK_SIZE * CHUNK_SIZE;

class ChunkSegment {
public:
    ChunkSegment(glm::ivec3 location);

    void SetBlock(int x, int y, int z, Block &block);

    void InitChunkSection();

    bool BuildMesh();
    void InitBuffers();
    void InitShaders();

    int GetIndex(int x, int y, int z) {
        return y * CHUNK_AREA + z * CHUNK_SIZE + x;
    }

    bool ShouldAddFace(const std::array<float, 18> &face, const glm::vec3 &position);
    int GetIndex(const glm::vec3 &position);
    void AddFace(const std::array<float, 18> &face, const glm::vec3 &position);
    void Render();

    int GetAmountOfBlocksInSegment();
private:
    std::array<Block, CHUNK_VOLUME> mBlocksInChunk;
    std::vector<glm::vec3> mChunkVertices;

    glm::ivec3 mLocation;

    bool mShouldRender = false;

    Shader* mShader;

    unsigned int mVAO, mVBO;
};


#endif
