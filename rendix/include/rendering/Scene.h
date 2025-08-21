#ifndef RENDIX_RENDERING_SCENE_H
#define RENDIX_RENDERING_SCENE_H

#include "rendering/IScene.h"

namespace rendix::rendering {

    class Scene : public IScene {
    public:
        Scene() = default;
        ~Scene() = default;

        void AddObject(std::shared_ptr<IMesh> mesh, std::shared_ptr<shaders::IShaderProgram> shaderProgram, const glm::mat4& modelMatrix = glm::mat4(1.0f)) override;
        const std::vector<SceneObject>& GetObjects() const override;

    private:
        std::vector<SceneObject> m_objects;
    };

} // namespace rendix::rendering

#endif //RENDIX_RENDERING_SCENE_H
