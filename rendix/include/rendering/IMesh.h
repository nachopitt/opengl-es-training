#ifndef RENDIX_RENDERING_IMESH_H
#define RENDIX_RENDERING_IMESH_H

#include <vector>
#include <glm/glm.hpp>
#include "rendering/Vertex.h"

namespace rendix::shaders {
    class IShaderProgram;
}

namespace rendix::rendering {

class IMesh {
public:
    virtual ~IMesh() = default;

    virtual const float* getVertices() const = 0;
    virtual const std::vector<uint32_t>& getIndices() const = 0;
    virtual const BufferLayout& getLayout() const = 0;

    virtual void setVertices(const float* vertices, size_t size) = 0;
    virtual void setIndices(const std::vector<uint32_t>& indices) = 0;
    virtual void setLayout(const BufferLayout& layout) = 0;

    virtual void Bind(shaders::IShaderProgram& shaderProgram) = 0;
    virtual void Unbind() = 0;
    virtual size_t getIndexCount() const = 0;
};

} // namespace rendix::rendering

#endif //RENDIX_RENDERING_IMESH_H
