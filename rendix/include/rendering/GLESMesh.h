#ifndef RENDIX_RENDERING_GLES_MESH_H
#define RENDIX_RENDERING_GLES_MESH_H

#include "rendering/IMesh.h"
#include "esUtil.h"

namespace rendix::rendering {

class GLESMesh : public IMesh {
public:
    GLESMesh();
    GLESMesh(const std::vector<Vertex>& vertices, const std::vector<uint32_t>& indices);
    ~GLESMesh();

    const std::vector<Vertex>& getVertices() const override;
    const std::vector<uint32_t>& getIndices() const override;
    GLuint getVBO() const;
    GLuint getIBO() const;

    void setVertices(const std::vector<Vertex>& vertices) override;
    void setIndices(const std::vector<uint32_t>& indices) override;

    void setupMesh();

private:
    std::vector<Vertex> m_vertices;
    std::vector<uint32_t> m_indices;
    GLuint m_vboId;
    GLuint m_iboId;
};

} // namespace rendix::rendering

#endif //RENDIX_RENDERING_GLES_MESH_H
