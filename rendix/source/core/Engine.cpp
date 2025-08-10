#include "core/Engine.h"
#include <iostream>
#include <chrono>

namespace rendix::core {

    Engine::Engine(IWindowSystem *windowSystem) : windowSystem(windowSystem), application(new Application)
    {
    }

    Engine::Engine(IWindowSystem *windowSystem, std::unique_ptr<Application> application) : windowSystem(windowSystem), application(std::move(application))
    {
    }

    bool Engine::Init(int width, int height, const std::string &windowTitleName)
    {
        onInit.Subscribe([this]() {
            application->OnInit(*this);
        });
        onShutdown.Subscribe([this]() {
            application->OnShutdown(*this);
        });

        windowSystem->onRender.Subscribe([this]() {
            application->OnRender(*this);
        });
        windowSystem->onUpdate.Subscribe([this](float delta) {
            application->OnUpdate(*this, delta);
        });
        windowSystem->onKey.Subscribe([this](unsigned char key, bool pressed) {
            application->OnKey(*this, key, pressed);
        });
        windowSystem->onMouse.Subscribe([this](int x, int y) {
            application->OnMouse(*this, x, y);
        });
        windowSystem->onResize.Subscribe([this](int width, int height) {
            application->OnWindowResize(*this, width, height);
        });

        if (!windowSystem->CreateWindow(width, height, windowTitleName))
        {
            std::cout << "Window creation failed" << std::endl;

            return false;
        }

        onInit.Notify();

        return true;
    }

    void Engine::Run()
    {
        std::unique_ptr<main_loop::IMainLoopStrategy> mainLoop = windowSystem->GetMainLoop();
        if (mainLoop) {
            mainLoop->Run(*windowSystem);
        }
        else {
            using clock = std::chrono::steady_clock;
            auto lastTime = clock::now();

            while (!windowSystem->ShouldClose()) {
                auto now = clock::now();
                float deltaTime = std::chrono::duration<float>(now - lastTime).count();
                lastTime = now;

                windowSystem->onUpdate.Notify(deltaTime);
                windowSystem->onRender.Notify();

                windowSystem->SwapBuffers();
                windowSystem->PollEvents();
            }
        }
    }
}
