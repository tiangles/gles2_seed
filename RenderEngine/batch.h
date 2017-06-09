#pragma once
#include <vector>
#include <memory>
#include "vec.h"
#include "matrix4x4.h"

namespace GLES2{
class RenderOperation;
class Matrix4x4;

class BatchConfig{
    unsigned int renderType;
    int priority;
    unsigned int textureId;
    Matrix4x4 modelMat;
};

struct Batch
{
    std::vector<std::shared_ptr<RenderOperation> > renderOperations;
};

}
