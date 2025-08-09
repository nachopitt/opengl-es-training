#include "core/Engine.h"
#include <iostream>

namespace rendix::core {

    Engine::Engine(IWindowSystem *windowSystem) : windowSystem(windowSystem), application(new Application)
    {
        windowSystem->onRender.Subscribe([this]() {
            application->OnRender();
        });
        windowSystem->onUpdate.Subscribe([this](float delta) {
            application->OnUpdate(delta);
        });
        windowSystem->onResize.Subscribe([this](int width, int height) {
            application->OnWindowResize(width, height);
        });
        windowSystem->onKey.Subscribe([this](unsigned char key, bool pressed) {
            application->OnKey(key, pressed);
        });
        windowSystem->onMouse.Subscribe([this](int x, int y) {
            application->OnMouse(x, y);
        });
    }

    Engine::Engine(IWindowSystem *windowSystem, std::unique_ptr<Application> application) : windowSystem(windowSystem), application(std::move(application))
    {
    }

    bool Engine::Init(int width, int height, const std::string &windowTitleName)
    {
        if (!windowSystem->CreateWindow(width, height, windowTitleName))
        {
            std::cout << "Window creation failed" << std::endl;

            return false;
        }

        return true;
    }

    int Engine::Run()
    {
        return windowSystem->Run();
    }
}
