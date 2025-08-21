#include "rendix-triangle/RendixTriangleApplication.h"
#include "core/Engine.h"
#include "utils/FileReader.h"
#include "core/RendixException.h"
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
        throw RendixException("Error loading vertex shader from " + vertexShaderFile);
    }

    fragmentShaderSource = fileReader.readTextFile(fragmentShaderFile);
    if (fragmentShaderSource.empty())
    {
        throw RendixException("Error loading fragment shader from " + fragmentShaderFile);
    }

    if (!vertexShader.Compile(vertexShaderSource))
    {
        throw RendixException("Error compiling vertex shader:\n" + vertexShader.GetErrorLog());
    }
    if (!fragmentShader.Compile(fragmentShaderSource))
    {
        throw RendixException("Error compiling fragment shader:\n" + fragmentShader.GetErrorLog());
    }

    if (!shaderProgram.AttachShader(vertexShader))
    {
        throw RendixException("Error attaching vertex shader to shader program");
    }
    if (!shaderProgram.AttachShader(fragmentShader))
    {
        throw RendixException("Error attaching fragment shader to shader program");
    }

    if (!shaderProgram.LinkShaders())
    {
        throw RendixException("Error linking shader program:\n" + shaderProgram.GetLinkLog());
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
