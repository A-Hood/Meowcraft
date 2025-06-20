#include "chunk.h"

Chunk::Chunk(glm::ivec3 location) :
    mLocation(location)
{
    CreateSections();
    std::cout << "Created Sections" << std::endl;
    for (int y = 0; y < CHUNK_SIZE; ++y) { // y axis
        for (int x = 0; x < CHUNK_SIZE; ++x){ // x axis
            for (int z = 0; z < CHUNK_SIZE; ++z) { // z axis
                SetBlock(x, y, z);
            }
        }
    }

    for (int i = 0; i < mChunkSegments.size(); i++) {
        mChunkSegments[i].InitChunkSection();
    }
}

void Chunk::CreateSections() {
    for(int i = 0; i < CHUNK_SIZE; i++) {
        mChunkSegments.emplace_back(glm::ivec3(mLocation.x, i, mLocation.z));
    }
}

void Chunk::SetBlock(int x, int y, int z) {
    if (y <= 0)
    {
        return;
    }

    Block block = Block(BlockType::dirt);

    int blockY = y % CHUNK_SIZE;
    mChunkSegments[y / CHUNK_SIZE].SetBlock(x, blockY, z, block);
}

void Chunk::RenderChunkSections() {
    for (int i = 0; i < mChunkSegments.size(); i++) {
        mChunkSegments[i].Render();
    }
}