#include "texture.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <stb_image/stb_image.h> // read image



Texture::Texture(int minX, int maxX, int minY, int maxY) {
    glGenTextures(1, &mTex);
    glBindTexture(GL_TEXTURE_2D, mTex);
    //glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);
}