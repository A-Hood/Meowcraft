#ifndef CHUNKMESH_H
#define CHUNKMESH_H

#include <iostream>
#include <vector>
#include <glm/glm.hpp>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "chunkconstants.h"

class ChunkMesh {
public:
    ChunkMesh() = default;

    void InitBuffers(); // add to builder

    void AddFace(const std::array<GLfloat, 18> &face,
                 const glm::vec3 &position,
                 const glm::vec3 chunkLocation);

    void SetTest(std::string hi) { test = hi; }
    std::string GetTest() { return test; }

    void Render();
private:
    std::vector<GLfloat> mChunkVertices;
    int mAmountOfVertices;

    std::string test;

    unsigned int mVAO, mVBO;
};


#endif
