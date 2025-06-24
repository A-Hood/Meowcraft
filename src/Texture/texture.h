#ifndef TEXTURE_H
#define TEXTURE_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <string>

class TextureAtlas;

class Texture {
public:
    Texture() = default;
    Texture(std::string fileName);

    void BindTexture() {
        glBindTexture(GL_TEXTURE_2D, mTex);
    }

private:
    unsigned int mTex;
};

#endif
