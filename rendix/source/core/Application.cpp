#include "core/Application.h"
#include <iostream>
#include "core/Engine.h"

namespace rendix::core {

    void Application::OnInit(Engine &engine)
    {
        std::cout << "Application OnInit" << std::endl;
    }

    void Application::OnRender(Engine &engine)
    {
        GLfloat vertices[] = {
            0.0f, 0.5f, 0.0f,
            -0.5f, -0.5f, 0.0f,
            0.5f, -0.5f, 0.0f,
        };

        engine.GetRenderer().SetClearColor(1.0f, 0.58f, 0.0f, 1.0f);
        engine.GetRenderer().Clear();
    }

    void Application::OnUpdate(Engine &engine, float deltaTime)
    {
        static float totaltime = 0;

        totaltime += deltaTime;
        if (totaltime > 2.0f)
        {
            std::cout << "Application OnUpdate: deltaTime: " << deltaTime << std::endl;
            totaltime -= 2.0f;
        }
    }

    void Application::OnKey(Engine &engine, unsigned char key, bool pressed)
    {
        std::cout << "Application OnKey: key: " << static_cast<int>(key) << ", pressed:"  << pressed << std::endl;
    }

    void Application::OnMouse(Engine &engine, int x, int y)
    {
        std::cout << "Application OnMouse: x: " << x << ", y: " << y << std::endl;
    }

    void Application::OnWindowResize(Engine &engine, int width, int height)
    {
        std::cout << "Application OnWindowResize: width: " << width << ", height: " << height << std::endl;
    }

    void Application::OnShutdown(Engine &engine)
    {
        std::cout << "Application OnShutdown" << std::endl;
    }
}
