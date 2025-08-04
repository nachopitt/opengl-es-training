#include "core/Engine.h"

namespace rendix::core {

    Engine::Engine():
        application(nullptr)
    {
    }

    void Engine::Init(GLint width, GLint height, const std::string &windowTitleName, GLuint flags)
    {
        esInitContext(&esContext);
        esContext.userData = this;

        esCreateWindow(&esContext, windowTitleName.c_str(), width, height, flags);

        esRegisterDrawFunc(&esContext, Engine::OnDraw);
        esRegisterKeyFunc(&esContext, Engine::OnKey);
        esRegisterUpdateFunc(&esContext, Engine::OnUpdate);
        esRegisterWindowResizeFunc(&esContext, Engine::OnWindowResize);
    }

    void Engine::OnDraw(ESContext *esContext)
    {
        Engine *_this = static_cast<Engine *>(esContext->userData);

        if (_this->application) {
            _this->application->OnDraw(esContext);
        }
    }

    void Engine::OnKey(ESContext *esContext, unsigned char key, int x, int y)
    {
        Engine *_this = static_cast<Engine *>(esContext->userData);
        if (_this->application)
        {
            _this->application->OnKey(esContext, key, x, y);
        }
    }

    void Engine::OnUpdate(ESContext *esContext, float deltaTime)
    {
        Engine *_this = static_cast<Engine *>(esContext->userData);
        if (_this->application)
        {
            _this->application->OnUpdate(esContext, deltaTime);
        }
    }

    void Engine::OnWindowResize(ESContext *esContext, int width, int height)
    {
        Engine *_this = static_cast<Engine *>(esContext->userData);
        if (_this->application)
        {
            _this->application->OnWindowResize(esContext, width, height);
        }
    }

    void Engine::Run()
    {
        esMainLoop(&esContext);
    }
}
