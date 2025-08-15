#ifndef RENDIX_TRIANGLE_APPLICATION_H
#define RENDIX_TRIANGLE_APPLICATION_H

#include "core/IApplication.h"
#include "shaders/GLESShader.h"
#include "shaders/GLESShaderProgram.h"

class RendixTriangleApplication : public rendix::core::IApplication {
public:
    RendixTriangleApplication();
    ~RendixTriangleApplication() = default;

    void OnInit(rendix::core::Engine &engine) override;
    void OnRender(rendix::core::Engine &engine) override;
    void OnUpdate(rendix::core::Engine &engine, float deltaTime) override;
    void OnKey(rendix::core::Engine &engine, unsigned char key, bool pressed) override;
    void OnMouse(rendix::core::Engine &engine, int x, int y) override;
    void OnWindowResize(rendix::core::Engine &engine, int width, int height) override;
    void OnShutdown(rendix::core::Engine &engine) override;

protected:
    rendix::shaders::GLESShader vertexShader;
    rendix::shaders::GLESShader fragmentShader;
    rendix::shaders::GLESShaderProgram shaderProgram;
};

#endif // RENDIX_TRIANGLE_APPLICATION_H
