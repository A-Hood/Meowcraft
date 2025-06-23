#include "chunk.h"

#include "chunkmanager.h"

Chunk::Chunk(ChunkManager &chunkManager, glm::ivec2 location) :
    mChunkManager(&chunkManager),
    mLocation(location)
{
    CreateSections();
    for (int y = 0; y < CHUNK_SIZE * mChunkSegments.size(); ++y) { // y axis
        for (int x = 0; x < CHUNK_SIZE; ++x){ // x axis
            for (int z = 0; z < CHUNK_SIZE; ++z) { // z axis
                if (y <= 50)
                    SetBlock(x, y, z, BlockType::dirt);
                else
                    SetBlock(x, y, z, BlockType::air);

            }
        }
    }
}

void Chunk::CreateSections() {
    for(int i = 0; i < CHUNK_SIZE; i++) {
        mChunkSegments.emplace_back(*mChunkManager, glm::ivec3(mLocation.x, i, mLocation.y));
    }
}

void Chunk::MakeMeshes() {
    for (ChunkSegment &chunkSeg : mChunkSegments) {
        chunkSeg.MakeMesh(); // makes and inits buffers
    }
};

void Chunk::SetBlock(int x, int y, int z, BlockType type) {
    if (y < 0)
    {
        return;
    }

    Block block = Block(type);
    int blockY = y % CHUNK_SIZE;
    mChunkSegments[y / CHUNK_SIZE].SetBlock(x, blockY, z, block);
}

/// Use to get block in from chunk -> chunk segment
BlockType Chunk::GetBlock(int x, int y, int z) {
    if (OutOfBounds(x,y,z)) {
        return BlockType::air;
    }

    int blockY = y % CHUNK_SIZE;
    return mChunkSegments[y / CHUNK_SIZE].GetBlock(x, blockY, z);
}

void Chunk::RenderChunks() {
    for (ChunkSegment &chunkSeg : mChunkSegments) {
        chunkSeg.RenderChunk(); // makes and inits buffers
    }
}

bool Chunk::OutOfBounds(int x, int y, int z) const noexcept
{
    if (x >= CHUNK_SIZE)
        return true;
    if (z >= CHUNK_SIZE)
        return true;

    if (x < 0)
        return true;
    if (y < 0)
        return true;
    if (z < 0)
        return true;

    if (y >= (int)mChunkSegments.size() * CHUNK_SIZE) {
        return true;
    }

    return false;
}
