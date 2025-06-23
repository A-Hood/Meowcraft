#include "chunkmeshbuilder.h"

#include "chunksegment.h"
#include "../Block/blockconstants.h"

struct AdjacentBlockPositions {
    void update(int x, int y, int z)
    {
        up = {x, y + 1, z};
        down = {x, y - 1, z};
        left = {x, y, z + 1};
        right = {x, y, z - 1};
        front = {x + 1, y, z};
        back = {x - 1, y, z};
    }

    glm::vec3 up;
    glm::vec3 down;
    glm::vec3 left;
    glm::vec3 right;
    glm::vec3 front;
    glm::vec3 back;
};

ChunkMeshBuilder::ChunkMeshBuilder(ChunkSegment &chunk, ChunkMesh &mesh) :
    mChunk(&chunk),
    mMesh(&mesh)
{
}


void ChunkMeshBuilder::BuildMesh() {
    AdjacentBlockPositions adjacent;

    for (unsigned int i = 0; i < CHUNK_VOLUME; i++) {
        int x = i % CHUNK_SIZE;
        int y = i / (CHUNK_SIZE * CHUNK_SIZE);
        int z = (i / CHUNK_SIZE) % CHUNK_SIZE;

        if (mChunk->GetBlock(x, y, z) == BlockType::air)
            continue;

        adjacent.update(x, y, z);

       //if ((mChunk->GetLocation().y != 0) || y != 0) {
        if (ShouldAddFace(BOTTOM_FACE, adjacent.down)) {
            mMesh->AddFace(BOTTOM_FACE, glm::vec3(x, y, z), mChunk->GetLocation());
        }
        //}
        if (ShouldAddFace(TOP_FACE, adjacent.up)) {
            mMesh->AddFace(TOP_FACE, glm::vec3(x, y, z), mChunk->GetLocation());
        }
        if (ShouldAddFace(LEFT_FACE, adjacent.left)) {
            mMesh->AddFace(LEFT_FACE, glm::vec3(x, y, z), mChunk->GetLocation());
        }
        if (ShouldAddFace(RIGHT_FACE, adjacent.right)) {
            mMesh->AddFace(RIGHT_FACE, glm::vec3(x, y, z), mChunk->GetLocation());
        }
        if (ShouldAddFace(FRONT_FACE, adjacent.front)) {
            mMesh->AddFace(FRONT_FACE, glm::vec3(x, y, z), mChunk->GetLocation());
        }
        if (ShouldAddFace(BACK_FACE, adjacent.back)) {
            mMesh->AddFace(BACK_FACE, glm::vec3(x, y, z), mChunk->GetLocation());
        }
    }
}

bool ChunkMeshBuilder::ShouldAddFace(const std::array<GLfloat, 18> &face, const glm::ivec3 &position) {
    auto blockType = mChunk->GetBlock(position.x, position.y, position.z);

    // check whether block at index
    if (blockType == BlockType::air) {
        return true;
    }

    return false;
}