#include "core/Engine.h"
#include <iostream>

namespace rendix::core {

    Engine::Engine():
        application(nullptr)
    {
    }

    bool Engine::Init(GLint width, GLint height, const std::string &windowTitleName, GLuint flags)
    {
        esInitContext(&esContext);
        esContext.userData = this;

        if (!windowManager.CreateWindow(esContext, width, height, windowTitleName, flags)) {
            std::cout << "Window creation failed" << std::endl;

            return false;
        }

        esRegisterDrawFunc(&esContext, Engine::OnDraw);
        esRegisterKeyFunc(&esContext, Engine::OnKey);
        esRegisterUpdateFunc(&esContext, Engine::OnUpdate);
        esRegisterWindowResizeFunc(&esContext, Engine::OnWindowResize);

        return true;
    }

    void Engine::OnDraw(ESContext *esContext)
    {
        Engine *_this = static_cast<Engine *>(esContext->userData);

        if (_this->application) {
            _this->application->OnDraw();
        }
    }

    void Engine::OnKey(ESContext *esContext, unsigned char key, int x, int y)
    {
        Engine *_this = static_cast<Engine *>(esContext->userData);
        if (_this->application)
        {
            _this->application->OnKey(key, x, y);
        }
    }

    void Engine::OnUpdate(ESContext *esContext, float deltaTime)
    {
        Engine *_this = static_cast<Engine *>(esContext->userData);
        if (_this->application)
        {
            _this->application->OnUpdate(deltaTime);
        }
    }

    void Engine::OnWindowResize(ESContext *esContext, int width, int height)
    {
        Engine *_this = static_cast<Engine *>(esContext->userData);
        if (_this->application)
        {
            _this->application->OnWindowResize(width, height);
        }
    }

    void Engine::Run()
    {
        esMainLoop(&esContext);
    }
}
