#include "core/Application.h"
#include <iostream>

namespace rendix::core {

    void Application::OnDraw() const {
        GLfloat vertices[] = {
            0.0f, 0.5f, 0.0f,
            -0.5f, -0.5f, 0.0f,
            0.5f, -0.5f, 0.0f,
        };
    }

    void Application::OnKey(unsigned char key, int x, int y) const {
        std::cout << "Application OnKey: key" << static_cast<int>(key) << ", x: " << x << "y: " << y << std::endl;
    }

    void Application::OnUpdate(float deltaTime) const {
        static float totaltime = 0;

        totaltime += deltaTime;
        if (totaltime > 2.0f)
        {
            std::cout << "Application OnUpdate: deltaTime" << deltaTime << std::endl;
            totaltime -= 2.0f;
        }
    }

    void Application::OnWindowResize(int width, int height) const {
        std::cout << "Application OnWindowResize: width" << width << ", height: " << height << std::endl;
    }
}
