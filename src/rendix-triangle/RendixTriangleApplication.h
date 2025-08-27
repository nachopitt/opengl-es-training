#ifndef RENDIX_TRIANGLE_APPLICATION_H
#define RENDIX_TRIANGLE_APPLICATION_H

#include "core/Application.h"
#include "shaders/GLESShader.h"
#include "shaders/GLESShaderProgram.h"
#include "rendering/GLESMesh.h"
#include "rendering/IScene.h"
#include <memory>
#include "core/Transform.h"
#include "core/Camera.h"

class RendixTriangleApplication : public rendix::core::Application {
public:
    RendixTriangleApplication();
    ~RendixTriangleApplication() = default;

    void SetupAttributes() override;
    void SetupScene() override;
    void OnUpdate(rendix::core::Engine &engine, float deltaTime) override;
    void OnRender(rendix::core::Engine &engine) override;
    void OnKey(rendix::core::Engine &engine, unsigned char key, bool pressed) override;
    void OnMouse(rendix::core::Engine &engine, int x, int y) override;
    void OnWindowResize(rendix::core::Engine &engine, int width, int height) override;

protected:
    std::shared_ptr<rendix::rendering::GLESMesh> triangleMesh;
    std::shared_ptr<rendix::core::Transform> m_transform;
    std::unique_ptr<rendix::core::Camera> m_camera;
};

#endif // RENDIX_TRIANGLE_APPLICATION_H
