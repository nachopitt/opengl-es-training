#ifndef RENDIX_CORE_APPLICATION_H
#define RENDIX_CORE_APPLICATION_H

#include "core/IApplication.h"
#include "shaders/Shader.h"
#include "shaders/ShaderProgram.h"

namespace rendix::core {

    class Engine;

    class Application : public IApplication {
    public:
        Application();
        virtual ~Application() = default;

        virtual void OnInit(Engine &engine);
        virtual void OnRender(Engine &engine);
        virtual void OnUpdate(Engine &engine, float deltaTime);
        virtual void OnKey(Engine &engine, unsigned char key, bool pressed);
        virtual void OnMouse(Engine &engine, int x, int y);
        virtual void OnWindowResize(Engine &engine, int width, int height);
        virtual void OnShutdown(Engine &engine);

    protected:
        shaders::Shader vertexShader;
        shaders::Shader fragmentShader;
        shaders::ShaderProgram shaderProgram;
    };

} // namespace rendix::rendering

#endif //RENDIX_CORE_APPLICATION_H
