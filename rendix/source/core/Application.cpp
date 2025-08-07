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
        std::cout << "Application OnWindowResize: key" << static_cast<int>(key) << ", x: " << x << "y: " << y << std::endl;
    }

    void Application::OnUpdate(float deltaTime) const {
        std::cout << "Application OnWindowResize: deltaTime" << deltaTime << std::endl;
    }

    void Application::OnWindowResize(int width, int height) const {
        std::cout << "Application OnWindowResize: width" << width << ", height: " << height << std::endl;
    }
}
