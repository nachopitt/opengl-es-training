#include "rendering/GLESMesh.h"
#include <vector>
#include "esUtil.h"
#include "rendering/GLESConvert.h"

namespace rendix::rendering {

    GLESMesh::GLESMesh() {
        m_vboId = 0;
        m_iboId = 0;
    }

    GLESMesh::GLESMesh(const float* vertices, size_t v_size, const std::vector<uint32_t>& indices, const BufferLayout& layout)
    {
        m_vertices.assign(vertices, vertices + v_size / sizeof(float));
        m_indices = indices;
        m_layout = layout;
        setupMesh();
    }

    GLESMesh::~GLESMesh() {
        glDeleteBuffers(1, &m_vboId);
        glDeleteBuffers(1, &m_iboId);
    }

    const float* GLESMesh::getVertices() const {
        return m_vertices.data();
    }

    const std::vector<uint32_t>& GLESMesh::getIndices() const
    {
        return m_indices;
    }

    const BufferLayout& GLESMesh::getLayout() const
    {
        return m_layout;
    }

    GLuint GLESMesh::getVBO() const {
        return m_vboId;
    }

    GLuint GLESMesh::getIBO() const {
        return m_iboId;
    }

    void GLESMesh::setVertices(const float* vertices, size_t size) {
        m_vertices.assign(vertices, vertices + size / sizeof(float));
        setupMesh();
    }

    void GLESMesh::setIndices(const std::vector<uint32_t>& indices) {
        m_indices = indices;
        setupMesh();
    }

    void GLESMesh::setLayout(const BufferLayout& layout) {
        m_layout = layout;
        setupMesh();
    }

    void GLESMesh::setupMesh() {
        if (m_vboId != 0) {
            glDeleteBuffers(1, &m_vboId);
        }
        if (m_iboId != 0) {
            glDeleteBuffers(1, &m_iboId);
        }

        glGenBuffers(1, &m_vboId);
        glBindBuffer(GL_ARRAY_BUFFER, m_vboId);
        glBufferData(GL_ARRAY_BUFFER, m_vertices.size() * sizeof(float), m_vertices.data(), GL_STATIC_DRAW);

        glGenBuffers(1, &m_iboId);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_iboId);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_indices.size() * sizeof(uint32_t), m_indices.data(), GL_STATIC_DRAW);
    }

    void GLESMesh::Bind(shaders::IShaderProgram& shaderProgram) {
        glBindBuffer(GL_ARRAY_BUFFER, m_vboId);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_iboId);

        const auto& layout = m_layout;
        for (const auto& element : layout)
        {
            GLint location = shaderProgram.GetAttributeLocation(element.Name);
            if (location != -1) {
                glEnableVertexAttribArray(location);
                glVertexAttribPointer(
                    location,
                    element.GetComponentCount(),
                    ShaderDataTypeToOpenGLBaseType(element.Type),
                    element.Normalized ? GL_TRUE : GL_FALSE,
                    layout.GetStride(),
                    (const void*)element.Offset
                );
            }
        }
    }

    void GLESMesh::Unbind() {
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }

    size_t GLESMesh::getIndexCount() const {
        return m_indices.size();
    }
}
