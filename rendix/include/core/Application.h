#ifndef RENDIX_CORE_APPLICATION_H
#define RENDIX_CORE_APPLICATION_H

#include "core/IApplication.h"
#include "shaders/GLESShader.h"
#include "shaders/GLESShaderProgram.h"

namespace rendix::core {

    class Engine;

    class Application : public IApplication {
    public:
        Application();

        void OnInit(Engine &engine) override;
        void OnRender(Engine &engine) override;
        void OnUpdate(Engine &engine, float deltaTime) override;
        void OnKey(Engine &engine, unsigned char key, bool pressed) override;
        void OnMouse(Engine &engine, int x, int y) override;
        void OnWindowResize(Engine &engine, int width, int height) override;
        void OnShutdown(Engine &engine) override;

    protected:
        shaders::GLESShader vertexShader;
        shaders::GLESShader fragmentShader;
        shaders::GLESShaderProgram shaderProgram;
    };

} // namespace rendix::rendering

#endif //RENDIX_CORE_APPLICATION_H
