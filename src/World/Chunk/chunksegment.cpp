#include "chunksegment.h"

#include "chunk.h"
#include "../Block/blockconstants.h"

// TODO: Add greedymesh algorithm to cut down on more tris.

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

ChunkSegment::ChunkSegment(glm::ivec3 location):
    mLocation(location)
{
}

void ChunkSegment::InitChunkSection() {
    mShouldRender = BuildMesh();

    if (mShouldRender){
        InitBuffers();
        std::cout << "Initialised Buffers" << std::endl;
        InitShaders();
        std::cout << "Initialised Shaders" << std::endl;
    }
}

// Initialise block in chunk
void ChunkSegment::SetBlock(int x, int y, int z, Block &block) {
    // oob check
    if (x >= CHUNK_SIZE || x < 0 ||
        y >= CHUNK_SIZE || y < 0 ||
        z >= CHUNK_SIZE || z < 0 ) {
        return;
    }
    //std::cout << "Blocks in chunk: " << mBlocksInChunk.size() <<"\nAttempting at index: " << GetIndex(x, y, z) << std::endl;
    mBlocksInChunk[GetIndex(x, y, z)] = block;
}

bool ChunkSegment::BuildMesh()
{
    AdjacentBlockPositions adjacent;

    for(unsigned int i = 0; i < CHUNK_VOLUME; i++)
    {
        if (mBlocksInChunk[i].GetBlockType() != BlockType::air)
        {
            std::cout << mBlocksInChunk[i].GetTypeString() << std::endl;
            int x = i % CHUNK_SIZE;
            int y = i / (CHUNK_SIZE * CHUNK_SIZE);
            int z = (i / CHUNK_SIZE) % CHUNK_SIZE;

            adjacent.update(x, y, z);

            if(ShouldAddFace(TOP_FACE, adjacent.up))
            {
                AddFace(TOP_FACE, glm::vec3(x, y, z));
            }
            if(ShouldAddFace(BOTTOM_FACE, adjacent.down))
            {
                AddFace(BOTTOM_FACE, glm::vec3(x, y, z));
            }
            if(ShouldAddFace(LEFT_FACE, adjacent.left))
            {
                AddFace(LEFT_FACE, glm::vec3(x, y, z));
            }
            if(ShouldAddFace(RIGHT_FACE, adjacent.right))
            {
                AddFace(RIGHT_FACE, glm::vec3(x, y, z));
            }
            if(ShouldAddFace(FRONT_FACE, adjacent.front))
            {
                AddFace(FRONT_FACE, glm::vec3(x, y, z));
            }
            if(ShouldAddFace(BACK_FACE, adjacent.back))
            {
                AddFace(BACK_FACE, glm::vec3(x, y, z));
            }
        }
    }

    if (mChunkVertices.size() != 0)
        return true;
    std::cout << "ERROR // NO VERTICES IN CHUNK: " << mLocation.x << ", " << mLocation.y << std::endl;
    return false;

}

bool ChunkSegment::ShouldAddFace(const std::array<float, 18> &face, const glm::vec3 &position) {
    // oob check
    if (position.x >= CHUNK_SIZE || position.x < 0 ||
        position.y >= CHUNK_SIZE || position.y < 0 ||
        position.z >= CHUNK_SIZE || position.z < 0 ) {
        return true;
    }

    // check whether block at index
    if (mBlocksInChunk[GetIndex(position)].GetBlockType() == BlockType::air)
    {
       // std::cout << mBlocksInChunk[GetIndex(position)].GetTypeString() << std::endl;
        return true;
    }

    return false;
}

int ChunkSegment::GetIndex(const glm::vec3 &position) {
    return position.y * CHUNK_AREA + position.z * CHUNK_SIZE + position.x;
}

void ChunkSegment::AddFace(const std::array<float, 18> &face, const glm::vec3 &position) {
    glm::vec3 vertex;
    for(int i = 0; i < sizeof(face) / sizeof(float);) {
        vertex.x = face[i++] + position.x + mLocation.x * CHUNK_SIZE;
        vertex.y = face[i++] + position.y + mLocation.y * CHUNK_SIZE;
        vertex.z = face[i++] + position.z + mLocation.z * CHUNK_SIZE;

        mChunkVertices.push_back(vertex);
    }
}

// opengl render stuffsies
void ChunkSegment::InitBuffers()
{
    glGenVertexArrays(1, &mVAO);
    glGenBuffers(1, &mVBO);
    glBindVertexArray(mVAO);
    glBindBuffer(GL_ARRAY_BUFFER, mVBO);
    glBufferData(GL_ARRAY_BUFFER, mChunkVertices.size() * sizeof(glm::vec3), &mChunkVertices[0], GL_STATIC_DRAW);
    std::cout << "Size of buffer: " << mChunkVertices.size() << std::endl;

    // Vertexes
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
}
void ChunkSegment::InitShaders()
{
    mShader = new Shader("../../src/Assets/Shaders/v.glsl", "../../src/Assets/Shaders/f.glsl");
    mShader->use();
    mShader->setVec3("objectColor", 1.0f, 0.5f, 0.31f);
    mShader->setVec3("lightColor",  1.0f, 1.0f, 1.0f);
}
void ChunkSegment::Render()
{
    if (mShouldRender) {
        glBindVertexArray(mVAO);
        glDrawArrays(GL_TRIANGLES, 0, mChunkVertices.size());
        glBindVertexArray(0);
    }
}