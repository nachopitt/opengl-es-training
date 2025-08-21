#include "rendering/Scene.h"

namespace rendix::rendering {

    void Scene::AddObject(std::shared_ptr<IMesh> mesh, std::shared_ptr<shaders::IShaderProgram> shaderProgram, const glm::mat4& modelMatrix) {
        m_objects.push_back({mesh, shaderProgram, modelMatrix});
    }

    const std::vector<SceneObject>& Scene::GetObjects() const {
        return m_objects;
    }

} // namespace rendix::rendering
