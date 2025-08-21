#ifndef RENDIX_RENDERING_GLES_MESH_H
#define RENDIX_RENDERING_GLES_MESH_H

#include "rendering/IMesh.h"
#include "esUtil.h"
#include "shaders/IShaderProgram.h"

namespace rendix::rendering {

class GLESMesh : public IMesh {
public:
    GLESMesh();
    GLESMesh(const float* vertices, size_t v_size, const std::vector<uint32_t>& indices, const BufferLayout& layout);
    ~GLESMesh();

    const float* getVertices() const override;
    const std::vector<uint32_t>& getIndices() const override;
    const BufferLayout& getLayout() const override;
    GLuint getVBO() const;
    GLuint getIBO() const;

    void setVertices(const float* vertices, size_t size) override;
    void setIndices(const std::vector<uint32_t>& indices) override;
    void setLayout(const BufferLayout& layout) override;

    void setupMesh();

    void Bind(shaders::IShaderProgram& shaderProgram) override;
    void Unbind() override;
    size_t getIndexCount() const override;

private:
    std::vector<float> m_vertices;
    std::vector<uint32_t> m_indices;
    BufferLayout m_layout;
    GLuint m_vboId;
    GLuint m_iboId;
};

} // namespace rendix::rendering

#endif //RENDIX_RENDERING_GLES_MESH_H
