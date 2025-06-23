#ifndef CHUNKMANAGER_H
#define CHUNKMANAGER_H

#include <unordered_map>
#include <glm/vec2.hpp>

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/hash.hpp>

#include "chunkconstants.h"

#include "chunk.h"

/// TODO: Add support for multiple chunks to be generated.
/// TODO: Add noise to randomise chunks.
/// TODO: Make sure faces inbetween chunks get culled.

class ChunkManager {
public:
    ChunkManager() = default;

    void InitChunks();

    Chunk GetChunk(glm::ivec2 &location);
    bool ChunkExists(glm::ivec2 location) const;

    void RenderChunks(); // make this load one chunk (testing for now)

private:
    std::unordered_map<glm::ivec2, Chunk> mChunkMap;
};

#endif
