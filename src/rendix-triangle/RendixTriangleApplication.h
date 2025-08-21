#ifndef RENDIX_TRIANGLE_APPLICATION_H
#define RENDIX_TRIANGLE_APPLICATION_H

#include "core/Application.h"
#include "shaders/GLESShader.h"
#include "shaders/GLESShaderProgram.h"
#include "rendering/GLESMesh.h"
#include "rendering/IScene.h"
#include <memory>

class RendixTriangleApplication : public rendix::core::Application {
public:
    RendixTriangleApplication();
    ~RendixTriangleApplication() = default;

    void OnInit(rendix::core::Engine &engine) override;
    void OnRender(rendix::core::Engine &engine) override;

protected:
    std::shared_ptr<rendix::rendering::GLESMesh> triangleMesh;
    std::shared_ptr<rendix::rendering::IScene> m_scene;
};

#endif // RENDIX_TRIANGLE_APPLICATION_H
