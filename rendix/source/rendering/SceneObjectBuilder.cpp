
#include "rendering/SceneObjectBuilder.h"
#include "rendering/IScene.h"
#include "core/Transform.h"

namespace rendix::rendering {

SceneObjectBuilder::SceneObjectBuilder() = default;
SceneObjectBuilder::~SceneObjectBuilder() = default;

SceneObjectBuilder& SceneObjectBuilder::WithMesh(std::shared_ptr<IMesh> mesh) {
    m_mesh = mesh;
    return *this;
}

SceneObjectBuilder& SceneObjectBuilder::WithShaderProgram(std::shared_ptr<shaders::IShaderProgram> shaderProgram) {
    m_shaderProgram = shaderProgram;
    return *this;
}

SceneObjectBuilder& SceneObjectBuilder::WithTexture(std::shared_ptr<texturing::ITexture> texture) {
    m_texture = texture;
    return *this;
}

SceneObjectBuilder& SceneObjectBuilder::WithTransform(std::shared_ptr<core::Transform> transform) {
    m_transform = transform;
    return *this;
}

SceneObject SceneObjectBuilder::Build() {
    if (!m_transform) {
        m_transform = std::make_shared<core::Transform>();
    }
    return SceneObject{m_mesh, m_shaderProgram, m_texture, m_transform};
}

} // namespace rendix::rendering
