#include "core/Application.h"
#include <iostream>
#include "core/Engine.h"

namespace rendix::core {

    Application::Application(): vertexShader(GL_VERTEX_SHADER), fragmentShader(GL_FRAGMENT_SHADER)
    {
    }

    void Application::OnInit(Engine &engine)
    {
        std::cout << "Application OnInit" << std::endl;

        std::string vertexShaderStr = R"(
attribute vec4 position;
void main()
{
   gl_Position = position;
})";
        std::string fragmentShaderStr = R"(
void main()
{
   gl_FragColor = vec4(1.0, 1.0, 1.0, 1.0);
})";

        if (!vertexShader.LoadFromString(vertexShaderStr))
        {
            std::cerr << "Error loading vertex shader" << std::endl;
        }
        if (!fragmentShader.LoadFromString(fragmentShaderStr))
        {
            std::cerr << "Error loading fragment shader" << std::endl;
        }

        if (!vertexShader.Compile())
        {
            std::cerr << "Error compiling vertex shader" << std::endl;
        }
        if (!fragmentShader.Compile())
        {
            std::cerr << "Error compiling fragment shader" << std::endl;
        }

        if (!shaderProgram.AttachShader(vertexShader))
        {
            std::cerr << "Error attaching vertex shader to shader program" << std::endl;
        }
        if (!shaderProgram.AttachShader(fragmentShader))
        {
            std::cerr << "Error attaching fragment shader to shader program" << std::endl;
        }

        if (!shaderProgram.LinkShaders())
        {
            std::cerr << "Error linking vertex and fragment shaders into the shader program" << std::endl;
        }

        if (!shaderProgram.Use())
        {
            std::cerr << "Error using shader program" << std::endl;
        }
    }

    void Application::OnRender(Engine &engine)
    {
        GLfloat vertices[] = {
            -0.5f, -0.5f, 0.0f,
            -0.5f, +0.5f, 0.0f,
            +0.5f, -0.5f, 0.0f,
            +0.5f, +0.5f, 0.0f,
        };

        engine.GetRenderer().SetClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        engine.GetRenderer().Clear();

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, vertices);
        glEnableVertexAttribArray(0);

        glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
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
