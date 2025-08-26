#include "rendering/Scene.h"

namespace rendix::rendering {

    void Scene::AddObject(const SceneObject& object) {
        m_objects.push_back(object);
    }

    const std::vector<SceneObject>& Scene::GetObjects() const {
        return m_objects;
    }

} // namespace rendix::rendering
