#ifndef CHUNK_H
#define CHUNK_H

#include "../Block/block.h"
#include "chunksegment.h"
#include "glm/gtc/matrix_transform.hpp"
#include <vector>

#include "chunkconstants.h"

class ChunkManager;

class Chunk {
public:
    Chunk() = default;
    Chunk(ChunkManager &chunkManager, glm::ivec2 location);

    void CreateSections();

    void SetBlock(int x, int y, int z, BlockType type);
    BlockType GetBlock(int x, int y, int z);
    int GetIndex(const glm::vec3 &position);

    void RenderChunks();

    bool OutOfBounds(int x, int y, int z) const noexcept;
private:
    glm::ivec2 mLocation;
    std::vector<ChunkSegment> mChunkSegments;

    ChunkManager *mChunkManager;
};


#endif
