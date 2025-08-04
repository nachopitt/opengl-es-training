#ifndef RENDIX_RENDERING_MESH
#define RENDIX_RENDERING_MESH

#include <vector>
#include <glm/glm.hpp>

namespace rendix::rendering {

struct Vertex {
    glm::vec3 position;
    glm::vec4 color;
};

class Mesh {
public:
    Mesh();
    Mesh(const std::vector<Vertex>& vertices, const std::vector<uint32_t>& indices);

    const std::vector<Vertex>& getVertices() const;
    const std::vector<uint32_t>& getIndices() const;

    void setVertices(const std::vector<Vertex>& vertices);
    void setIndices(const std::vector<uint32_t>& indices);

private:
    std::vector<Vertex> m_vertices;
    std::vector<uint32_t> m_indices;
};

} // namespace rendix::rendering

#endif //RENDIX_RENDERING_MESH
