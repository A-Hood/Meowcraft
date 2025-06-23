#ifndef BLOCKCONSTANTS_H
#define BLOCKCONSTANTS_H
#include <array>

const std::array<GLfloat, 18> TOP_FACE { // pos y
        0, 1, 0,  1, 1, 0,  1, 1, 1,  1, 1, 1,  0, 1, 1,  0, 1, 0
};
const std::array<GLfloat, 18> BOTTOM_FACE { // neg y
        0, 0, 0,  1, 0, 0,  1, 0, 1,  1, 0, 1,  0, 0, 1,  0, 0, 0
};
const std::array<GLfloat, 18> LEFT_FACE { // pos z
        0, 0, 1,  1, 0, 1,  1, 1, 1,  1, 1, 1,  0, 1, 1,  0, 0, 1
};
const std::array<GLfloat, 18> RIGHT_FACE { // neg z
        0, 0, 0,  1, 0, 0,  1, 1, 0,  1, 1, 0,  0, 1, 0,  0, 0, 0
};
const std::array<GLfloat, 18> FRONT_FACE { // pos x
        1, 1, 1,  1, 1, 0,  1, 0, 0,  1, 0, 0,  1, 0, 1,  1, 1, 1
};
const std::array<GLfloat, 18> BACK_FACE { // neg x
        0, 1, 1,  0, 1, 0,  0, 0, 0,  0, 0, 0,  0, 0, 1,  0, 1, 1
};

const std::array<GLfloat, 12> FRONT_TEX_COORDS { // x
    1, 0,  1, 1,  0, 1,  0, 1,  0, 0,  1, 0
};
const std::array<GLfloat, 12> TOP_TEX_COORDS { // y
    0, 1,  1, 1,  1, 0,  1, 0,  0, 0,  0, 1
};
const std::array<GLfloat, 12> SIDE_TEX_COORDS { // z
    0, 0,  1, 0,  1, 1,  1, 1,  0, 1,  0, 0,

};

#endif