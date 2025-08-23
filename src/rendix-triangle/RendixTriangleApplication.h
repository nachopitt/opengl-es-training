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

    void SetupAttributes() override;
    void SetupScene() override;

protected:
    std::shared_ptr<rendix::rendering::GLESMesh> triangleMesh;
};

#endif // RENDIX_TRIANGLE_APPLICATION_H
