#include "rendering/Mesh.h"
#include <vector>
#include "esUtil.h"

namespace rendix::rendering {

    Mesh::Mesh() {
    }

    Mesh::Mesh(const std::vector<Vertex> &vertices, const std::vector<uint32_t> &indices):
        m_vertices(vertices), m_indices(indices) {
    }

    const std::vector<Vertex> & Mesh::getVertices() const {
        return m_vertices;
    }

    const std::vector<uint32_t> & Mesh::getIndices() const
    {
        return m_indices;
    }

    void Mesh::setVertices(const std::vector<Vertex> &vertices) {
        m_vertices = vertices;
    }

    void Mesh::setIndices(const std::vector<uint32_t> &indices) {
        m_indices = indices;
    }
}
