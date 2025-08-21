#include "rendix-triangle/RendixTriangleApplication.h"
#include "core/Engine.h"
#include "utils/FileReader.h"
#include "core/RendixException.h"
#include <iostream>
#include <string>
#include <vector>

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

RendixTriangleApplication::RendixTriangleApplication() {
    const std::string vertexShaderFile = "shaders/basic-color.vs";
    const std::string fragmentShaderFile = "shaders/basic.fs";

    FileReader fileReader;
    vertexShaderStr = fileReader.readTextFile(vertexShaderFile);
    if (vertexShaderStr.empty())
    {
        throw RendixException("Error loading vertex shader from " + vertexShaderFile);
    }

    fragmentShaderStr = fileReader.readTextFile(fragmentShaderFile);
    if (fragmentShaderStr.empty())
    {
        throw RendixException("Error loading fragment shader from " + fragmentShaderFile);
    }
}

void RendixTriangleApplication::OnInit(rendix::core::Engine &engine) {
    std::cout << "RendixTriangleApplication OnInit" << std::endl;

    Application::OnInit(engine);

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
