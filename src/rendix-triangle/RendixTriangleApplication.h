#ifndef RENDIX_TRIANGLE_APPLICATION_H
#define RENDIX_TRIANGLE_APPLICATION_H

#include "core/Application.h"
#include "shaders/GLESShader.h"
#include "shaders/GLESShaderProgram.h"
#include "rendering/GLESMesh.h"
#include "rendering/IScene.h"
#include <memory>
#include "core/Transform.h"

class RendixTriangleApplication : public rendix::core::Application {
public:
    RendixTriangleApplication();
    ~RendixTriangleApplication() = default;

    void SetupAttributes() override;
    void SetupScene() override;
    void OnUpdate(rendix::core::Engine &engine, float deltaTime) override;

protected:
    std::shared_ptr<rendix::rendering::GLESMesh> triangleMesh;
    std::shared_ptr<rendix::core::Transform> m_transform;
};

#endif // RENDIX_TRIANGLE_APPLICATION_H
