#include "rendix-triangle/RendixTriangleApplication.h"
#include "core/Engine.h"
#include "utils/FileReader.h"
#include <iostream>
#include <string>
#include <vector>

using namespace rendix::core;
using namespace rendix::shaders;
using namespace rendix::utils;
using namespace rendix::rendering;

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

    // Create the triangle mesh
    std::vector<Vertex> vertices = {
        {glm::vec3(-0.5f, -0.5f, 0.0f), glm::vec4(1.0f, 0.58f, 0.0f, 1.0f)},
        {glm::vec3(0.0f, 0.5f, 0.0f), glm::vec4(1.0f, 0.95f, 0.0f, 1.0f)},
        {glm::vec3(0.5f, -0.5f, 0.0f), glm::vec4(1.0f, 0.58f, 0.0f, 1.0f)},
    };
    std::vector<uint32_t> indices = {0, 1, 2};
    triangleMesh.setVertices(vertices);
    triangleMesh.setIndices(indices);
}

void RendixTriangleApplication::OnRender(rendix::core::Engine &engine) {
    engine.GetRenderer().SetClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    engine.GetRenderer().Clear();

    engine.GetRenderer().Draw(triangleMesh, shaderProgram);
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
