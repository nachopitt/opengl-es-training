#ifndef RENDIX_RENDERING_I_SCENE_H
#define RENDIX_RENDERING_I_SCENE_H

#include <vector>
#include <memory>
#include <glm/glm.hpp>

#include "rendering/IMesh.h"
#include "shaders/IShaderProgram.h"
#include "texturing/ITexture.h"
#include "core/Transform.h"
#include "rendering/SceneObjectBuilder.h"

namespace rendix::rendering {

    struct SceneObject {
        std::shared_ptr<IMesh> mesh;
        std::shared_ptr<shaders::IShaderProgram> shaderProgram;
        std::shared_ptr<texturing::ITexture> texture;
        std::shared_ptr<core::Transform> transform;

        static SceneObjectBuilder CreateBuilder() {
            return SceneObjectBuilder();
        }
    };

    class IScene {
    public:
        virtual ~IScene() = default;
        virtual void AddObject(const SceneObject& object) = 0;
        virtual const std::vector<SceneObject>& GetObjects() const = 0;
    };

} // namespace rendix::rendering

#endif //RENDIX_RENDERING_I_SCENE_H
