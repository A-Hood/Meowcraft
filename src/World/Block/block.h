#ifndef BLOCK_H
#define BLOCK_H

#include <iostream>
#include <array>
#include <vector>
#include "glm/glm.hpp"

enum class BlockType {
    air = 0,
    grass = 1,
    dirt = 2,
    stone = 3,
};

struct BlockData {
    glm::vec2 xTexCoords;
    glm::vec2 yTexCoords;
    glm::vec2 zTexCoords;

};

struct MeshFace {
    std::vector<glm::vec3> sVertexes;
    std::vector<glm::vec2> sTexCoords;
    std::vector<glm::vec3> sNormals;

    MeshFace(std::vector<glm::vec3> vertexes) {
        sVertexes = vertexes;
    };
};



class Block {
public:
    Block() = default;
    Block(BlockType type);

    BlockType GetBlockType() {
        return mType;
    }

private:
    BlockType mType;

    // TODO - Add normals/tex coords to apply textures and shading.
};

#endif