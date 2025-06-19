#ifndef BLOCKCONSTANTS_H
#define BLOCKCONSTANTS_H
#include <array>

const std::array<float, 18> TOP_FACE { // pos y
        -0.5f, 0.5f, -0.5f,  0.5f, 0.5f, -0.5f,  0.5f, 0.5f, 0.5f,  0.5f, 0.5f, 0.5f,  -0.5f, 0.5f, 0.5f,  -0.5f, 0.5f, -0.5f
};
const std::array<float, 18> BOTTOM_FACE { // neg y
        -0.5f, -0.5f, -0.5f,  0.5f, -0.5f, -0.5f,  0.5f, -0.5f, 0.5f,  0.5f, -0.5f, 0.5f,  -0.5f, -0.5f, 0.5f,  -0.5f, -0.5f, -0.5f
};
const std::array<float, 18> LEFT_FACE { // pos z
        -0.5f, -0.5f, 0.5f,  0.5f, -0.5f, 0.5f,  0.5f, 0.5f, 0.5f,  0.5f, 0.5f, 0.5f,  -0.5f, 0.5f, 0.5f,  -0.5f, -0.5f, 0.5f
};
const std::array<float, 18> RIGHT_FACE { // neg z
        -0.5f, -0.5f, -0.5f,  0.5f, -0.5f, -0.5f,  0.5f, 0.5f, -0.5f,  0.5f, 0.5f, -0.5f,  -0.5f, 0.5f, -0.5f,  -0.5f, -0.5f, -0.5f
};
const std::array<float, 18> FRONT_FACE { // pos x
        0.5f, 0.5f, 0.5f,  0.5f, 0.5f, -0.5f,  0.5f, -0.5f, -0.5f,  0.5f, -0.5f, -0.5f,  0.5f, -0.5f, 0.5f,  0.5f, 0.5f, 0.5f
};
const std::array<float, 18> BACK_FACE { // neg x
        -0.5f, 0.5f, 0.5f,  -0.5f, 0.5f, -0.5f,  -0.5f, -0.5f, -0.5f,  -0.5f, -0.5f, -0.5f,  -0.5f, -0.5f, 0.5f,  -0.5f, 0.5f, 0.5f
};



#endif
