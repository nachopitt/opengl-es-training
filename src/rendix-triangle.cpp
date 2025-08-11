#include "shaders/Shader.h"
#include "shaders/ShaderProgram.h"
#include "core/ESUtilWindowSystem.h"
#include "core/Engine.h"
#include "rendering/OpenGLESRenderer.h"
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

    rendix::rendering::OpenGLESRenderer renderer(width, height);
    rendix::core::Engine engine(&windowSystem, &renderer);

    if (!engine.Init()) {
        std::cerr << "Engine initialization failed" << std::endl;

        return false;
    }

    rendix::shaders::Shader vertexShader(GL_VERTEX_SHADER);
    rendix::shaders::Shader fragmentShader(GL_FRAGMENT_SHADER);
    rendix::shaders::ShaderProgram shaderProgram;

    vertexShader.LoadFromFile("shaders/basic-color.vs");
    fragmentShader.LoadFromFile("shaders/basic.fs");

    vertexShader.Compile();
    fragmentShader.Compile();

    shaderProgram.AttachShader(vertexShader);
    shaderProgram.AttachShader(fragmentShader);

    shaderProgram.LinkShaders();

    engine.Run();

    return 0;
}
