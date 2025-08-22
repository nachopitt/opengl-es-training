#ifndef RENDIX_RENDERING_I_SCENE_H
#define RENDIX_RENDERING_I_SCENE_H

#include <vector>
#include <memory>
#include <glm/glm.hpp>

#include "rendering/IMesh.h"
#include "shaders/IShaderProgram.h"
#include "texturing/ITexture.h"

namespace rendix::rendering {

    struct SceneObject {
        std::shared_ptr<IMesh> mesh;
        std::shared_ptr<shaders::IShaderProgram> shaderProgram;
        std::shared_ptr<texturing::ITexture> texture;
        glm::mat4 modelMatrix; // Transformation matrix for the object
    };

    class IScene {
    public:
        virtual ~IScene() = default;
        virtual void AddObject(std::shared_ptr<IMesh> mesh, std::shared_ptr<shaders::IShaderProgram> shaderProgram, std::shared_ptr<texturing::ITexture> texture, const glm::mat4& modelMatrix = glm::mat4(1.0f)) = 0;
        virtual void AddObject(std::shared_ptr<IMesh> mesh, std::shared_ptr<shaders::IShaderProgram> shaderProgram, const glm::mat4& modelMatrix = glm::mat4(1.0f)) = 0;
        virtual const std::vector<SceneObject>& GetObjects() const = 0;
    };

} // namespace rendix::rendering

#endif //RENDIX_RENDERING_I_SCENE_H
