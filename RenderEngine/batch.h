#pragma once
#include <vector>
#include <memory>

namespace GLES2{
class RenderOperation;
class Matrix4x4;

struct Batch
{
    std::vector<std::shared_ptr<RenderOperation> > renderOperations;
};

}
