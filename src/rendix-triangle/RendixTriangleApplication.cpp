#include "rendix-triangle/RendixTriangleApplication.h"
#include "core/Engine.h"
#include "utils/FileReader.h"
#include "core/RendixException.h"
#include <iostream>
#include <string>
#include <vector>
#include "rendering/Scene.h"
#include <memory>

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

void RendixTriangleApplication::SetupScene() {
    // Create the triangle mesh
    triangleMesh = std::make_shared<GLESMesh>();
    float vertices[] = {
        -0.5f, -0.5f, 0.0f, 1.0f, 0.58f, 0.0f, 1.0f, // Bottom-left
        0.0f,  0.5f, 0.0f, 1.0f, 0.95f, 0.0f, 1.0f, // Top-middle
        0.5f, -0.5f, 0.0f, 1.0f, 0.58f, 0.0f, 1.0f  // Bottom-right
    };
    std::vector<uint32_t> indices = {0, 1, 2};

    BufferLayout layout = {
        {ShaderDataType::Float3, "a_Position"},
        {ShaderDataType::Float4, "a_Color"}
    };

    triangleMesh->setVertices(vertices, sizeof(vertices));
    triangleMesh->setIndices(indices);
    triangleMesh->setLayout(layout);

    // Create scene and add objects
    m_scene = std::make_shared<Scene>();
    m_scene->AddObject(triangleMesh, shaderProgram);
}
