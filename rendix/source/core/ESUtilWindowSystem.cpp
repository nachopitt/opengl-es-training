#include "core/ESUtilWindowSystem.h"
#include "main_loop/ESUtilMainLoopStrategy.h"
#include <string>
#include "esUtil.h"

extern "C" {
    GLboolean userInterrupt(ESContext *esContext);
}

namespace rendix::core {

    ESUtilWindowSystem::ESUtilWindowSystem() : shouldClose(false)
    {
        esInitContext(&esContext);
        esContext.userData = this;

        esRegisterDrawFunc(&esContext, ESUtilWindowSystem::OnDraw);
        esRegisterKeyFunc(&esContext, ESUtilWindowSystem::OnKey);
        esRegisterUpdateFunc(&esContext, ESUtilWindowSystem::OnUpdate);
        esRegisterWindowResizeFunc(&esContext, ESUtilWindowSystem::OnWindowResize);
    }

    bool ESUtilWindowSystem::CreateWindow(int width, int height, const std::string &title)
    {
        return esCreateWindow(&esContext, title.c_str(), width, height, ES_WINDOW_RGB);
    }

    void ESUtilWindowSystem::SwapBuffers() {
        eglSwapBuffers(esContext.eglDisplay, esContext.eglSurface);
    }

    void ESUtilWindowSystem::PollEvents() {
        if (userInterrupt(&esContext) == GL_TRUE)
        {
            shouldClose = true;
        }
    }

    bool ESUtilWindowSystem::ShouldClose() {
        return shouldClose;
    }

    std::unique_ptr<main_loop::IMainLoopStrategy> ESUtilWindowSystem::GetMainLoop()
    {
        return std::unique_ptr<main_loop::IMainLoopStrategy>(new main_loop::ESUtilMainLoopStrategy);
    }

    int ESUtilWindowSystem::GetWidth() const {
        return esContext.width;
    }

    int ESUtilWindowSystem::GetHeight() const {
        return esContext.height;
    }

    ESContext &ESUtilWindowSystem::GetContext() {
        return esContext;
    }

    void ESUtilWindowSystem::OnDraw(ESContext *esContext)
    {
        ESUtilWindowSystem *_this = static_cast<ESUtilWindowSystem *>(esContext->userData);
        _this->onRender.Notify();
    }

    void ESUtilWindowSystem::OnKey(ESContext *esContext, unsigned char key, int x, int y)
    {
        ESUtilWindowSystem *_this = static_cast<ESUtilWindowSystem *>(esContext->userData);
        _this->onKey.Notify(key, true);
        _this->onMouse.Notify(x, y);
    }

    void ESUtilWindowSystem::OnUpdate(ESContext *esContext, float deltaTime)
    {
        ESUtilWindowSystem *_this = static_cast<ESUtilWindowSystem *>(esContext->userData);
        _this->onUpdate.Notify(deltaTime);
    }

    void ESUtilWindowSystem::OnWindowResize(ESContext *esContext, int width, int height)
    {
        ESUtilWindowSystem *_this = static_cast<ESUtilWindowSystem *>(esContext->userData);
        _this->onResize.Notify(width, height);
    }
}
