#ifndef BLOCK_H
#define BLOCK_H

#include <iostream>
#include <array>
#include <vector>
#include <glm/glm.hpp>

struct BlockData {
    enum Type {
        DIRT,
        STONE,
        GRASS,
        SAND
    };

    Type sType;
};

class Block {
public:
    Block(BlockData::Type type);

    std::array<float, 108> GetBlockVertices() { return mBlockVertices; };
    // TODO - Implement these
    glm::vec2 GetUV();
    glm::vec3 GetTexCoords();

    void SetBlockPos(const glm::vec3 pos) { mBlockPosition = pos; };
    const glm::vec3 GetBlockPos() { return this->mBlockPosition; }

    void Render();
private:
    BlockData mData;

    glm::vec3 mBlockPosition;

    // TODO - Add normals/tex coords to apply textures and shading.
    const std::array<float, 108> mBlockVertices = {
            // Bottom (-z axis)
            -0.5f, -0.5f, -0.5f,
            0.5f, -0.5f, -0.5f,
            0.5f, 0.5f, -0.5f,
            0.5f, 0.5f, -0.5f,
            -0.5f, 0.5f, -0.5f,
            -0.5f, -0.5f, -0.5f,
            // Top (+z axis)
            -0.5f, -0.5f, 0.5f,
            0.5f, -0.5f, 0.5f,
            0.5f, 0.5f, 0.5f,
            0.5f, 0.5f, 0.5f,
            -0.5f, 0.5f, 0.5f,
            -0.5f, -0.5f, 0.5f,
            // (-x axis)
            -0.5f, 0.5f, 0.5f,
            -0.5f, 0.5f, -0.5f,
            -0.5f, -0.5f, -0.5f,
            -0.5f, -0.5f, -0.5f,
            -0.5f, -0.5f, 0.5f,
            -0.5f, 0.5f, 0.5f,
            // (+x axis)
            0.5f, 0.5f, 0.5f,
            0.5f, 0.5f, -0.5f,
            0.5f, -0.5f, -0.5f,
            0.5f, -0.5f, -0.5f,
            0.5f, -0.5f, 0.5f,
            0.5f, 0.5f, 0.5f,
            // (-y axis)
            -0.5f, -0.5f, -0.5f,
            0.5f, -0.5f, -0.5f,
            0.5f, -0.5f, 0.5f,
            0.5f, -0.5f, 0.5f,
            -0.5f, -0.5f, 0.5f,
            -0.5f, -0.5f, -0.5f,
            // (+y axis)
            -0.5f, 0.5f, -0.5f,
            0.5f, 0.5f, -0.5f,
            0.5f, 0.5f, 0.5f,
            0.5f, 0.5f, 0.5f,
            -0.5f, 0.5f, 0.5f,
            -0.5f, 0.5f, -0.5f,
    };
};

#endif