#include "shaders/Shader.h"
#include "shaders/ShaderProgram.h"
#include "core/ESUtilWindowSystem.h"
#include "core/Engine.h"
#include "rendering/GLESRenderer.h"
#include "rendix-triangle/RendixTriangleApplication.h"
#include <iostream>

int main(int argc, char* argv[])
{
    const int width = 640;
    const int height = 480;

    rendix::core::ESUtilWindowSystem windowSystem;

    if (!windowSystem.CreateWindow(width, height, "Rendix Triangle OpenGL ES example"))
    {
        std::cerr << "Window creation failed" << std::endl;

        return false;
    }

    RendixTriangleApplication application;
    rendix::rendering::GLESRenderer renderer(width, height);
    rendix::core::Engine engine(&windowSystem, &renderer, &application);

    if (!engine.Init()) {
        std::cerr << "Engine initialization failed" << std::endl;

        return false;
    }

    engine.Run();

    return 0;
}
