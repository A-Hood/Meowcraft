#include "chunkmanager.h"

void ChunkManager::InitChunks() {
    for (int x = 0; x < CHUNK_SIZE; ++x){ // x axis
        for (int z = 0; z < CHUNK_SIZE; ++z) { // z axis
            glm::ivec2 pos{x, z};
            Chunk chunk{*this, glm::ivec2(x, z)};
            mChunkMap.emplace(pos, std::move(chunk));
        }
    }

    for (int x = 0; x < CHUNK_SIZE; ++x) { // x axis
        for (int z = 0; z < CHUNK_SIZE; ++z) { // z axis
            mChunkMap[glm::ivec2(x, z)].MakeMeshes();
        }
    }
}

void ChunkManager::RenderChunks() {
    for (int x = 0; x < CHUNK_SIZE; ++x) { // x axis
        for (int z = 0; z < CHUNK_SIZE; ++z) { // z axis
            mChunkMap[glm::ivec2(x, z)].RenderChunks();
        }
    }
}

Chunk ChunkManager::GetChunk(glm::ivec2 &location) {
    if (ChunkExists(location))
        return mChunkMap[location];
    return Chunk();
}

// Locate whether chunk exists in map
bool ChunkManager::ChunkExists(glm::ivec2 location) const {
    return mChunkMap.find(location) != mChunkMap.end();
}