#include "chunkmesh.h"

#include "../Block/blockconstants.h"

ChunkMesh::ChunkMesh() {
    mTexture = Texture("hi");
}

void ChunkMesh::AddFace(const std::array<GLfloat, 18> &face,
                        const std::array<GLfloat, 12> &texCoords,
                        const glm::vec3 &position,
                        const glm::vec3 chunkLocation) {
    glm::vec3 vertex;

    int itr = 0;
    for(int i = 0; i < sizeof(face) / sizeof(GLfloat);) {

        vertex.x = face[i++] + chunkLocation.x * CHUNK_SIZE + position.x;
        vertex.y = face[i++] + chunkLocation.y * CHUNK_SIZE + position.y;
        vertex.z = face[i++] + chunkLocation.z * CHUNK_SIZE + position.z;

        // insert 3 vertices
        mChunkVertices.push_back(vertex.x);
        mChunkVertices.push_back(vertex.y);
        mChunkVertices.push_back(vertex.z);
        // insert 2 tex coords
        mChunkVertices.push_back(texCoords[itr++]);
        mChunkVertices.push_back(texCoords[itr++]);
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
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (void*)0);
        glEnableVertexAttribArray(0);
        // Tex Coords
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));
        glEnableVertexAttribArray(1);


        std::cout << "Size of vertex buffer: " <<  (mChunkVertices.size() / 5) * 3 << "\n";
        std::cout << "Size of tex coord buffer: " <<  (mChunkVertices.size() / 5) * 2 << "\n";
    }
}

void ChunkMesh::Render()
{
    if (mAmountOfVertices != 0) {
        glDisable(GL_BLEND);

        glBindVertexArray(mVAO);
        mTexture.BindTexture();
        glDrawArrays(GL_TRIANGLES, 0, mChunkVertices.size());
        glBindVertexArray(0);
    }
}
