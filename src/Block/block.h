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
    Block(BlockData::Type type, glm::vec3 pos);

    //glm::vec3 GetBlockPos() { return this->mBlockPosition; };

    // TODO - Implement these
    /*
    glm::vec2 GetUV();
    glm::vec3 GetTexCoords();
    */

private:
    BlockData mData;
    glm::vec3 mBlockPosition;

    // TODO - Add normals/tex coords to apply textures and shading.
};

#endif