#ifndef RENDIX_RENDERING_IMESH_H
#define RENDIX_RENDERING_IMESH_H

#include <vector>
#include <glm/glm.hpp>

namespace rendix::rendering {

struct Vertex {
    glm::vec3 position;
    glm::vec4 color;
};

class IMesh {
public:
    virtual ~IMesh() = default;

    virtual const std::vector<Vertex>& getVertices() const = 0;
    virtual const std::vector<uint32_t>& getIndices() const = 0;

    virtual void setVertices(const std::vector<Vertex>& vertices) = 0;
    virtual void setIndices(const std::vector<uint32_t>& indices) = 0;

    virtual void Bind() = 0;
    virtual void Unbind() = 0;
    virtual size_t getIndexCount() const = 0;
};

} // namespace rendix::rendering

#endif //RENDIX_RENDERING_IMESH_H
