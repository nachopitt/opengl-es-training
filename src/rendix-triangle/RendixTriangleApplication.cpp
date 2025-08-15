#include "rendix-triangle/RendixTriangleApplication.h"
#include "core/Engine.h"
#include "utils/FileReader.h"
#include <iostream>
#include <string>

using namespace rendix::core;
using namespace rendix::shaders;
using namespace rendix::utils;

RendixTriangleApplication::RendixTriangleApplication() : vertexShader(ShaderType::VERTEX), fragmentShader(ShaderType::FRAGMENT)
{
}

void RendixTriangleApplication::OnInit(rendix::core::Engine &engine) {
    const std::string vertexShaderFile = "shaders/basic-color.vs";
    const std::string fragmentShaderFile = "shaders/basic.fs";

    std::cout << "RendixTriangleApplication OnInit" << std::endl;

    FileReader fileReader;
    std::string vertexShaderSource;
    std::string fragmentShaderSource;

    vertexShaderSource = fileReader.readTextFile(vertexShaderFile);
    if (vertexShaderSource.empty())
    {
        std::cerr << "Error loading vertex shader" << std::endl;
    }

    fragmentShaderSource = fileReader.readTextFile(fragmentShaderFile);
    if (fragmentShaderSource.empty())
    {
        std::cerr << "Error loading fragment shader" << std::endl;
    }

    if (!vertexShader.Compile(vertexShaderSource))
    {
        std::cerr << "Error compiling vertex shader" << std::endl;
    }
    if (!fragmentShader.Compile(fragmentShaderSource))
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

    if (!shaderProgram.Use()) {
        std::cerr << "Error using shader program" << std::endl;
    }
}

void RendixTriangleApplication::OnRender(rendix::core::Engine &engine) {
    GLfloat vertices[] = {
        -0.5f, -0.5f, 0.0f,
        +0.0f, +0.5f, 0.0f,
        +0.5f, -0.5f, 0.0f,
    };

    GLfloat colors[] = {
        +1.0f, +0.58f, 0.0f,
        +1.0f, +0.95f, 0.0f,
        +1.0f, +0.58f, 0.0f,
    };

    engine.GetRenderer().SetClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    engine.GetRenderer().Clear();

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, vertices);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, colors);
    glEnableVertexAttribArray(1);

    glDrawArrays(GL_TRIANGLE_STRIP, 0, 3);
}

void RendixTriangleApplication::OnUpdate(rendix::core::Engine &engine, float deltaTime) {

}

void RendixTriangleApplication::OnKey(rendix::core::Engine &engine, unsigned char key, bool pressed) {

}

void RendixTriangleApplication::OnMouse(rendix::core::Engine &engine, int x, int y) {

}

void RendixTriangleApplication::OnWindowResize(rendix::core::Engine &engine, int width, int height) {

}

void RendixTriangleApplication::OnShutdown(rendix::core::Engine &engine) {

}
