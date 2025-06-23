#ifndef CHUNKMESHBUILDER_H
#define CHUNKMESHBUILDER_H

#include <vector>
#include <glm/glm.hpp>

#include <glad/glad.h>
#include <GLFW/glfw3.h>


class ChunkSegment;
class ChunkMesh;

class ChunkMeshBuilder {
public:
    ChunkMeshBuilder(ChunkSegment &chunk, ChunkMesh &mesh);

    void BuildMesh();

    bool ShouldAddFace(const std::array<GLfloat, 18> &face, const glm::ivec3 &position);
private:
    ChunkSegment *mChunk = nullptr;
    ChunkMesh *mMesh = nullptr;
};


#endif
