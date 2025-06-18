#include "block.h"

Block::Block(BlockData::Type type, glm::vec3 pos)
{
    // store type in data
    mData.sType = type;
    mBlockPosition = pos;
};