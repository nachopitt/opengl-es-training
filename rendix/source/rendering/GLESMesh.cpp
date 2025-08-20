#include "rendering/GLESMesh.h"
#include <vector>
#include "esUtil.h"

namespace rendix::rendering {

    GLESMesh::GLESMesh() {
        setupMesh();
    }

    GLESMesh::GLESMesh(const std::vector<Vertex> &vertices, const std::vector<uint32_t> &indices):
        m_vertices(vertices), m_indices(indices) {
        setupMesh();
    }

    GLESMesh::~GLESMesh() {
        glDeleteBuffers(1, &m_vboId);
        glDeleteBuffers(1, &m_iboId);
    }

    const std::vector<Vertex> & GLESMesh::getVertices() const {
        return m_vertices;
    }

    const std::vector<uint32_t> & GLESMesh::getIndices() const
    {
        return m_indices;
    }

    GLuint GLESMesh::getVBO() const {
        return m_vboId;
    }

    GLuint GLESMesh::getIBO() const {
        return m_iboId;
    }

    void GLESMesh::setVertices(const std::vector<Vertex> &vertices) {
        m_vertices = vertices;
        setupMesh();
    }

    void GLESMesh::setIndices(const std::vector<uint32_t> &indices) {
        m_indices = indices;
        setupMesh();
    }

    void GLESMesh::setupMesh() {
        glGenBuffers(1, &m_vboId);
        glBindBuffer(GL_ARRAY_BUFFER, m_vboId);
        glBufferData(GL_ARRAY_BUFFER, m_vertices.size() * sizeof(Vertex), m_vertices.data(), GL_STATIC_DRAW);

        glGenBuffers(1, &m_iboId);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_iboId);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_indices.size() * sizeof(uint32_t), m_indices.data(), GL_STATIC_DRAW);
    }

    void GLESMesh::Bind() {
        glBindBuffer(GL_ARRAY_BUFFER, m_vboId);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_iboId);
    }

    void GLESMesh::Unbind() {
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }

    size_t GLESMesh::getIndexCount() const {
        return m_indices.size();
    }
}
