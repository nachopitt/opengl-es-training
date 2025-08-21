#ifndef RENDIX_CORE_APPLICATION_H
#define RENDIX_CORE_APPLICATION_H

#include "core/IApplication.h"
#include "shaders/GLESShader.h"
#include "shaders/GLESShaderProgram.h"
#include "rendering/IScene.h"
#include <string>
#include <memory>

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

        virtual void SetupShaders();
        virtual void SetupScene();

    protected:
        std::shared_ptr<shaders::GLESShader> vertexShader;
        std::shared_ptr<shaders::GLESShader> fragmentShader;
        std::shared_ptr<shaders::GLESShaderProgram> shaderProgram;

        std::string vertexShaderStr;
        std::string fragmentShaderStr;

        std::shared_ptr<rendix::rendering::IScene> m_scene;
    };

} // namespace rendix::core

#endif //RENDIX_CORE_APPLICATION_H
