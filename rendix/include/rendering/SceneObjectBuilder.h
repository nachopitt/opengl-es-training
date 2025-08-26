
#ifndef RENDIX_RENDERING_SCENEOBJECTBUILDER_H
#define RENDIX_RENDERING_SCENEOBJECTBUILDER_H

#include <memory>

namespace rendix::core {
    class Transform;
}

namespace rendix::shaders {
    class IShaderProgram;
}

namespace rendix::texturing {
    class ITexture;
}

namespace rendix::rendering {

class IMesh;
struct SceneObject;

class SceneObjectBuilder {
public:
    SceneObjectBuilder();
    ~SceneObjectBuilder();

    SceneObjectBuilder& WithMesh(std::shared_ptr<IMesh> mesh);
    SceneObjectBuilder& WithShaderProgram(std::shared_ptr<shaders::IShaderProgram> shaderProgram);
    SceneObjectBuilder& WithTexture(std::shared_ptr<texturing::ITexture> texture);
    SceneObjectBuilder& WithTransform(std::shared_ptr<core::Transform> transform);

    SceneObject Build();

private:
    std::shared_ptr<IMesh> m_mesh;
    std::shared_ptr<shaders::IShaderProgram> m_shaderProgram;
    std::shared_ptr<texturing::ITexture> m_texture;
    std::shared_ptr<core::Transform> m_transform;
};

} // namespace rendix::rendering

#endif // RENDIX_RENDERING_SCENEOBJECTBUILDER_H
