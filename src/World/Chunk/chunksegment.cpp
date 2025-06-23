#include "chunksegment.h"

#include "chunkmeshbuilder.h"

#include "chunkmanager.h" // used to get other chunks around current chunk

#include <string>

ChunkSegment::ChunkSegment(ChunkManager &chunkManager, glm::ivec3 location):
    mChunkManager(&chunkManager),
    mLocation(location) {
}


void ChunkSegment::MakeMesh() {
    ChunkMeshBuilder(*this, mChunkMesh).BuildMesh();
    std::string hi = std::to_string(mLocation.x) + ", " + std::to_string(mLocation.z);
    mChunkMesh.SetTest(hi);
    mChunkMesh.InitBuffers();

}

// Initialise block in chunk
void ChunkSegment::SetBlock(int x, int y, int z, Block &block) {
    // oob check
    if (x >= CHUNK_SIZE || x < 0 ||
        y >= CHUNK_SIZE || y < 0 ||
        z >= CHUNK_SIZE || z < 0 ) {
        return;
    }

    mBlocksInChunk[GetIndex(x, y, z)] = block;
}

BlockType ChunkSegment::GetBlock(int x, int y, int z) {
    // oob check
    if (x >= CHUNK_SIZE || x < 0 ||
        y >= CHUNK_SIZE || y < 0 ||
        z >= CHUNK_SIZE || z < 0 ) {
        auto location = glm::ivec3(mLocation.x * CHUNK_SIZE + x, mLocation.y * CHUNK_SIZE + y,
                                   mLocation.z * CHUNK_SIZE + z);
        auto chunkLocation = glm::ivec2(location.x / CHUNK_SIZE, location.z / CHUNK_SIZE);
        auto blockLocation = glm::ivec2(location.x % CHUNK_SIZE, location.z % CHUNK_SIZE);

        return mChunkManager->GetChunk(chunkLocation).GetBlock(blockLocation.x, location.y, blockLocation.y);
    }

    return mBlocksInChunk[GetIndex(x, y, z)].GetBlockType();
}

const glm::vec3 ChunkSegment::GetLocation() const {
    return mLocation;
}