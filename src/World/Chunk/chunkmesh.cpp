#include "chunkmesh.h"

#include "../Block/blockconstants.h"


void ChunkMesh::AddFace(const std::array<GLfloat, 18> &face, const glm::vec3 &position, const glm::vec3 chunkLocation) {
    glm::vec3 vertex;

    for(int i = 0; i < sizeof(face) / sizeof(GLfloat);) {

        vertex.x = face[i++] + chunkLocation.x * CHUNK_SIZE + position.x;
        vertex.y = face[i++] + chunkLocation.y * CHUNK_SIZE + position.y;
        vertex.z = face[i++] + chunkLocation.z * CHUNK_SIZE + position.z;

        mChunkVertices.push_back(vertex.x);
        mChunkVertices.push_back(vertex.y);
        mChunkVertices.push_back(vertex.z);
    }
}

// opengl render stuffsies
void ChunkMesh::InitBuffers()
{
    if (mChunkVertices.size() != 0)
    {
        glGenVertexArrays(1, &mVAO);
        glGenBuffers(1, &mVBO);
        glBindVertexArray(mVAO);
        glBindBuffer(GL_ARRAY_BUFFER, mVBO);
        glBufferData(GL_ARRAY_BUFFER, mChunkVertices.size() * sizeof(GLfloat), &mChunkVertices[0], GL_STATIC_DRAW);

        // Vertexes
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void*)0);
        glEnableVertexAttribArray(0);

        //std::cout << "Size of buffer: " <<  mChunkVertices.size() << std::endl;
    }
}

void ChunkMesh::Render()
{
    if (mAmountOfVertices != 0) {
        glBindVertexArray(mVAO);
        glDrawArrays(GL_TRIANGLES, 0, mChunkVertices.size());
        glBindVertexArray(0);
    }
}
