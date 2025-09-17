#include "rendering/GLESRenderer.h"
#include "rendering/GLESMesh.h"
#include "shaders/IShaderProgram.h"
#include "texturing/GLESTexture.h"
#include "esUtil.h"
#include "rendering/IScene.h"
#include "core/Transform.h"
#include "core/Camera.h"
#include "rendering/PerspectiveProjectionStrategy.h"

namespace rendix::rendering {

    using namespace shaders;
    using namespace texturing;
    using namespace core;

    // Static default camera for the Draw(IScene& scene) overload
    static Camera s_defaultCamera(glm::vec3(0.0f, 0.0f, 3.0f));

    void GLESRenderer::Init()
    {
        glEnable(GL_DEPTH_TEST); // Enable depth testing
        glDisable(GL_CULL_FACE); // Disable back-face culling
        // Initialize default camera's projection strategy
        s_defaultCamera.SetProjectionStrategy(std::make_unique<PerspectiveProjectionStrategy>(45.0f, 800.0f / 600.0f, 0.1f, 100.0f));
    }

    GLESRenderer::GLESRenderer(int width, int height) : IRenderer(width, height)
    {
    }

    void GLESRenderer::Draw(IScene &scene) // New overload implementation
    {
        Draw(scene, s_defaultCamera); // Call the other Draw overload with the default camera
    }

    void GLESRenderer::Draw(IScene &scene, const Camera& camera)
    {
        for (const auto& object : scene.GetObjects()) {
            object.shaderProgram->Use();
            object.mesh->Bind(*object.shaderProgram);

            if (object.texture) {
                object.texture->bind(0); // Bind to texture unit 0
                object.shaderProgram->SetUniform("u_Texture", 0); // Set uniform to texture unit 0
            }

            object.shaderProgram->SetUniform("u_ModelMatrix", object.transform->GetModelMatrix());
            object.shaderProgram->SetUniform("u_ViewMatrix", camera.GetViewMatrix());
            object.shaderProgram->SetUniform("u_ProjectionMatrix", camera.GetProjectionMatrix());

            glDrawElements(GL_TRIANGLES, object.mesh->getIndexCount(), GL_UNSIGNED_INT, 0);

            if (object.texture) {
                object.texture->unbind();
            }

            object.mesh->Unbind();
        }
    }

    void GLESRenderer::SetClearColor(float r, float g, float b, float a) {
        glClearColor(r, g, b, a);
    }

    void GLESRenderer::Clear()
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    void GLESRenderer::Resize(int width, int height)
    {
        glViewport(0, 0, width, height);
    }
}
