#ifndef RENDIX_RENDERING_SCENE_H
#define RENDIX_RENDERING_SCENE_H

#include "rendering/IScene.h"

namespace rendix::rendering {

    class Scene : public IScene {
    public:
        Scene() = default;
        ~Scene() = default;

        void AddObject(const SceneObject& object) override;
        const std::vector<SceneObject>& GetObjects() const override;

    private:
        std::vector<SceneObject> m_objects;
    };

} // namespace rendix::rendering

#endif //RENDIX_RENDERING_SCENE_H
