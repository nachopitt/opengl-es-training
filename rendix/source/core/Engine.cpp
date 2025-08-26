#include "core/Engine.h"
#include <iostream>
#include <chrono>
#include "core/Application.h"

namespace rendix::core {

    Engine::Engine(IWindowSystem *windowSystem, rendering::IRenderer *renderer) : windowSystem(windowSystem), renderer(renderer), application(new Application)
    {
    }

    Engine::Engine(IWindowSystem *windowSystem, rendering::IRenderer *renderer, IApplication *application) : windowSystem(windowSystem), renderer(renderer), application(application)
    {
    }

    bool Engine::Init()
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

        onShutdown.Notify();
    }

    IWindowSystem &Engine::GetWindowSystem() const {
        return *windowSystem;
    }

    rendering::IRenderer &Engine::GetRenderer() const {
        return *renderer;
    }
}
