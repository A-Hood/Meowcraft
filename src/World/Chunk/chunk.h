#ifndef CHUNK_H
#define CHUNK_H

#include "../Block/block.h"
#include "chunksegment.h"
#include "../../Shader/Shader.h"
#include "glm/gtc/matrix_transform.hpp"
#include <vector>

#include "glad/glad.h"
#include "GLFW/glfw3.h"

class Chunk {
public:
    Chunk(glm::ivec3 location);

    void CreateSections();
    void SetBlock(int x, int y, int z, BlockType type);
    void RenderChunkSections();

    int GetAmountOfBlocksInChunk();
private:
    glm::ivec3 mLocation;
    std::vector<ChunkSegment> mChunkSegments;

};


#endif
