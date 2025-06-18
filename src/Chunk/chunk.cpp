#include "chunk.h"

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
                Block *block = new Block(BlockData::Type::DIRT);
                block->SetBlockPos(glm::vec3(x, y, z));
                mBlocksInChunk.push_back(block);
            }
        }
    }
}

void Chunk::BuildMesh()
{
    for(Block* block : mBlocksInChunk)
    {
        glm::vec3 vertex;
        for (int i = 0; i < sizeof(block->GetBlockVertices()) / sizeof(float) ;)
        {
            vertex.x = block->GetBlockVertices()[i++] + block->GetBlockPos().x;
            vertex.y = block->GetBlockVertices()[i++] + block->GetBlockPos().y;
            vertex.z = block->GetBlockVertices()[i++] + block->GetBlockPos().z;

            mChunkVertices.push_back(vertex);
        }
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