#include "core/ESUtilWindowSystem.h"
#include "core/Engine.h"
#include "rendering/GLESRenderer.h"
#include "rendix-triangle/RendixTriangleApplication.h"
#include "core/RendixException.h"
#include <iostream>

int main(int argc, char* argv[])
{
    try {
        const int width = 640;
        const int height = 480;

        rendix::core::ESUtilWindowSystem windowSystem;

        if (!windowSystem.CreateWindow(width, height, "Rendix Triangle OpenGL ES example"))
        {
            throw rendix::core::RendixException("Window creation failed");
        }

        RendixTriangleApplication application;
        rendix::rendering::GLESRenderer renderer(width, height);
        rendix::core::Engine engine(&windowSystem, &renderer, &application);

        if (!engine.Init()) {
            throw rendix::core::RendixException("Engine initialization failed");
        }

        engine.Run();

    } catch (const rendix::core::RendixException& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    } catch (const std::exception& e) {
        std::cerr << "An unexpected error occurred: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}
