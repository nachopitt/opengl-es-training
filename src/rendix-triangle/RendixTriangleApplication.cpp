#include "rendix-triangle/RendixTriangleApplication.h"
#include "core/Engine.h"
#include <iostream>
#include <string>

RendixTriangleApplication::RendixTriangleApplication() : vertexShader(GL_VERTEX_SHADER), fragmentShader(GL_FRAGMENT_SHADER)
{
}

void RendixTriangleApplication::OnInit(rendix::core::Engine &engine) {
    const std::string vertexShaderFile = "shaders/basic-color.vs";
    const std::string fragmentShaderFile = "shaders/basic.fs";

    std::cout << "RendixTriangleApplication OnInit" << std::endl;

    if (!vertexShader.LoadFromFile(vertexShaderFile))
    {
        std::cerr << "Error loading vertex shader" << std::endl;
    }
    if (!fragmentShader.LoadFromFile(fragmentShaderFile))
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

    glUseProgram(shaderProgram.GetShaderProgramId());

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, vertices);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, colors);

    glEnableVertexAttribArray(0);
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
