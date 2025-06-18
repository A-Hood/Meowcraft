#include "chunk.h"
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

Chunk::Chunk() {
    InitChunk();
    std::cout << "Initialised Chunk" << std::endl;
    BuildMesh();
    std::cout << "Built Mesh" << std::endl;
    InitBuffers();
    std::cout << "Initialised Buffers" << std::endl;
    InitShaders();
    std::cout << "Initialised Shaders" << std::endl;
}

void Chunk::InitChunk() {
    for (int y = 0; y < CHUNK_SIZE; ++y) { // y axis
        for (int x = 0; x < CHUNK_SIZE; ++x){ // x axis
            for (int z = 0; z < CHUNK_SIZE; ++z) { // z axis
                auto *block = new Block(BlockData::Type::DIRT, glm::vec3{x, y, z});
                mBlocksInChunk.push_back(block);
                std::cout << "Block initialised at postion: " << mBlocksInChunk.size() << std::endl;
            }
        }
    }
}

void Chunk::BuildMesh()
{
    AdjacentBlockPositions adjacent;
    for(unsigned int i = 0; i < CHUNK_VOLUME; i++)
    {
        int x = i % CHUNK_SIZE;
        int y = i / (CHUNK_SIZE * CHUNK_SIZE);
        int z = (i / CHUNK_SIZE) % CHUNK_SIZE;

        //std::cout << i << std::endl;
        adjacent.update(x, y, z);
        //std::cout << adjacent.down.x << ", " << adjacent.down.y << ", " << adjacent.down.z << std::endl;

        if(ShouldAddFace(TOP_FACE, adjacent.up))
        {
            AddFace(TOP_FACE, glm::vec3(x, y, z));
            //std::cout << "TOP_FACE" << std::endl;
        }
        if(ShouldAddFace(BOTTOM_FACE, adjacent.down))
        {
            AddFace(BOTTOM_FACE, glm::vec3(x, y, z));
            //std::cout << "BOTTOM_FACE" << std::endl;
        }
        if(ShouldAddFace(LEFT_FACE, adjacent.left))
        {
            AddFace(LEFT_FACE, glm::vec3(x, y, z));
            //std::cout << "LEFT_FACE" << std::endl;
        }
        if(ShouldAddFace(RIGHT_FACE, adjacent.right))
        {
            AddFace(RIGHT_FACE, glm::vec3(x, y, z));
            //std::cout << "RIGHT_FACE" << std::endl;
        }
        if(ShouldAddFace(FRONT_FACE, adjacent.front))
        {
            AddFace(FRONT_FACE, glm::vec3(x, y, z));
            //std::cout << "FRONT_FACE" << std::endl;
        }
        if(ShouldAddFace(BACK_FACE, adjacent.back))
        {
            AddFace(BACK_FACE, glm::vec3(x, y, z));
            //std::cout << "BACK_FACE" << std::endl;
        }
    }
    std::cout << "Size of mesh: " << mChunkVertices.size() << std::endl;
}

bool Chunk::ShouldAddFace(const std::array<float, 18> &face, const glm::vec3 &position) {
    if (position.x >= CHUNK_SIZE || position.x < 0 ||
       position.y >= CHUNK_SIZE || position.y < 0 ||
       position.z >= CHUNK_SIZE || position.z < 0 ) {
        std::cout << position.x << ", " << position.y << ", " << position.z << std::endl;
        return true;
    }

    if (mBlocksInChunk[GetIndex(position)] == NULL)
    {
        std::cout << position.x << ", " << position.y << ", " << position.z << std::endl;
        return true;
    }

    return false;
}

int Chunk::GetIndex(const glm::vec3 &position) {
    std::cout << position.y * CHUNK_AREA + position.z * CHUNK_SIZE + position.x << std::endl;
    return position.y * CHUNK_AREA + position.z * CHUNK_SIZE + position.x;
}

void Chunk::AddFace(const std::array<float, 18> &face, const glm::vec3 &position) {
    glm::vec3 vertex;
    for(int i = 0; i < sizeof(face) / sizeof(float);) {
        vertex.x = face[i++] + position.x;
        vertex.y = face[i++] + position.y;
        vertex.z = face[i++] + position.z;

        mChunkVertices.push_back(vertex);
    }
}

void Chunk::InitBuffers()
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

void Chunk::InitShaders()
{
    mShader = new Shader("../../src/Assets/Shaders/v.glsl", "../../src/Assets/Shaders/f.glsl");
    mShader->use();
    mShader->setVec3("objectColor", 1.0f, 0.5f, 0.31f);
    mShader->setVec3("lightColor",  1.0f, 1.0f, 1.0f);
}

void Chunk::Render()
{
    glBindVertexArray(mVAO);
    glDrawArrays(GL_TRIANGLES, 0, mChunkVertices.size());
    glBindVertexArray(0);
}