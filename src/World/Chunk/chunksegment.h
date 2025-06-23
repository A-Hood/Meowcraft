#ifndef CHUNKSEGMENT_H
#define CHUNKSEGMENT_H

#include "../Block/block.h"
#include "../../Shader/Shader.h"
#include "glm/gtc/matrix_transform.hpp"
#include <vector>

#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include "chunkconstants.h"
#include "chunkmesh.h"

class ChunkManager;

class ChunkSegment {
public:
    ChunkSegment(ChunkManager &chunkManager, glm::ivec3 location);

    void MakeMesh();

    void SetBlock(int x, int y, int z, Block &block);
    BlockType GetBlock(int x, int y, int z);

    int GetIndex(int x, int y, int z) {
        return y * CHUNK_AREA + z * CHUNK_SIZE + x;
    }
    const glm::vec3 GetLocation() const;

    void RenderChunk() {
        mChunkMesh.Render();
    }
private:
    std::array<Block, CHUNK_VOLUME> mBlocksInChunk;

    ChunkManager *mChunkManager;

    ChunkMesh mChunkMesh;

    glm::ivec3 mLocation;

    unsigned int mVAO, mVBO;
};


#endif
