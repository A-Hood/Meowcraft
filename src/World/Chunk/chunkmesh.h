#ifndef CHUNKMESH_H
#define CHUNKMESH_H

#include <iostream>
#include <vector>
#include <glm/glm.hpp>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "chunkconstants.h"

#include "../../Texture/texture.h"

class ChunkMesh {
public:
    ChunkMesh();

    void InitBuffers(); // add to builder

    void AddFace(const std::array<GLfloat, 18> &face,
                 const std::array<GLfloat, 12> &texCoords,
                 const glm::vec3 &position,
                 const glm::vec3 chunkLocation);

    void Render();
private:
    std::vector<GLfloat> mChunkVertices;
    std::vector<GLfloat> mChunkTexCoords;
    int mAmountOfVertices;

    Texture mTexture;

    unsigned int mVAO, mVBO;
};

#endif