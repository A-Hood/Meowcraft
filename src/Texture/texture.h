#ifndef TEXTURE_H
#define TEXTURE_H

class Texture {
public:
    Texture() = default;
    Texture(int minX, int maxX, int minY, int maxY);

private:
    unsigned int mTex;
};

#endif
