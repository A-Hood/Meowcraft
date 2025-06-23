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
    std::cout << "Created mesh at location: " << mLocation.y << std::endl;
    std::string hi = std::to_string(mLocation.x) + ", " + std::to_string(mLocation.z);
    mChunkMesh.SetTest(hi);
    mChunkMesh.InitBuffers();
    std::cout << "Init buffers" << std::endl;

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
        auto blockLocation = glm::ivec3(location.x % CHUNK_SIZE, location.y, location.z % CHUNK_SIZE);

        //std::cout << "\n\nWorld Pos: " << location.x << ", " << location.y << ", " << location.z <<
        //             "\nConverted Chunk Location: " << chunkLocation.x << ", " << chunkLocation.y <<
        //             "\nConverted Block Location: " << blockLocation.x << ", " << blockLocation.y << ", " << blockLocation.z << "\n";

        //std::cout << "\n\nThis Chunk: " << mLocation.x << ", " << mLocation.y << ", " << mLocation.y <<
        //            "\nThis Block: " << x << ", " << y << ", " << z <<
        //            "\nConverted Chunk Location: " << chunkLocation.x << ", " << chunkLocation.y << "\n";

        return mChunkManager->GetChunk(chunkLocation).GetBlock(blockLocation.x, blockLocation.y, blockLocation.z);
    }

    return mBlocksInChunk[GetIndex(x, y, z)].GetBlockType();
}

const glm::vec3 ChunkSegment::GetLocation() const {
    return mLocation;
}