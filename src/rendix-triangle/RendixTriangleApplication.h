#ifndef RENDIX_TRIANGLE_APPLICATION_H
#define RENDIX_TRIANGLE_APPLICATION_H

#include "core/Application.h"
#include "shaders/GLESShader.h"
#include "shaders/GLESShaderProgram.h"
#include "rendering/GLESMesh.h"

class RendixTriangleApplication : public rendix::core::Application {
public:
    RendixTriangleApplication();
    ~RendixTriangleApplication() = default;

    void OnInit(rendix::core::Engine &engine) override;
    void OnRender(rendix::core::Engine &engine) override;

protected:
    rendix::shaders::GLESShader vertexShader;
    rendix::shaders::GLESShader fragmentShader;
    rendix::shaders::GLESShaderProgram shaderProgram;
    rendix::rendering::GLESMesh triangleMesh;
};

#endif // RENDIX_TRIANGLE_APPLICATION_H
