#include "rendix-triangle/RendixTriangleApplication.h"
#include "core/Engine.h"
#include "utils/FileReader.h"
#include "core/RendixException.h"
#include <iostream>
#include <string>
#include <vector>
#include "rendering/Scene.h"
#include <memory>
#include "core/Transform.h"
#include "core/Camera.h"
#include "rendering/PerspectiveProjectionStrategy.h"

using namespace rendix::core;
using namespace rendix::shaders;
using namespace rendix::utils;
using namespace rendix::rendering;
using namespace rendix::texturing;

RendixTriangleApplication::RendixTriangleApplication() {
    const std::string vertexShaderFile = "shaders/basic-texture.vs";
    const std::string fragmentShaderFile = "shaders/basic-texture.fs";

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

    // Initialize camera
    m_camera = std::make_unique<Camera>(glm::vec3(0.0f, 0.0f, 3.0f));
    m_camera->SetProjectionStrategy(std::make_unique<PerspectiveProjectionStrategy>(45.0f, 800.0f / 600.0f, 0.1f, 100.0f));
}

void RendixTriangleApplication::SetupAttributes()
{
    shaderProgram->BindAttribute(0, "a_Position");
    shaderProgram->BindAttribute(1, "a_Color");
    shaderProgram->BindAttribute(2, "a_TexCoord");
}

void RendixTriangleApplication::SetupScene() {
    // Create the triangle mesh
    triangleMesh = std::make_shared<GLESMesh>();
    float vertices[] = {
        -0.5f, -0.5f, 0.0f, 1.0f, 0.58f, 0.0f, 1.0f, 0.0f, 0.0f, // Bottom-left
        0.0f,  0.5f, 0.0f, 1.0f, 0.95f, 0.0f, 1.0f, 0.5f, 1.0f, // Top-middle
        0.5f, -0.5f, 0.0f, 1.0f, 0.58f, 0.0f, 1.0f, 1.0f, 0.0f  // Bottom-right
    };
    std::vector<uint32_t> indices = {0, 1, 2};

    BufferLayout layout = {
        {ShaderDataType::Float3, "a_Position"},
        {ShaderDataType::Float4, "a_Color"},
        {ShaderDataType::Float2, "a_TexCoord"}
    };

    triangleMesh->setVertices(vertices, sizeof(vertices));
    triangleMesh->setIndices(indices);
    triangleMesh->setLayout(layout);

    std::shared_ptr<rendix::texturing::ITexture> texture = rendix::texturing::ITexture::create("assets/textures/checkerboard.jpg");

    // Create scene and add objects
    m_scene = std::make_shared<Scene>();
    m_transform = std::make_shared<Transform>();

    auto sceneObject = SceneObject::CreateBuilder()
        .WithMesh(triangleMesh)
        .WithShaderProgram(shaderProgram)
        .WithTexture(texture)
        .WithTransform(m_transform)
        .Build();

    m_scene->AddObject(sceneObject);
}

void RendixTriangleApplication::OnUpdate(Engine &engine, float deltaTime) {
    // Rotate the triangle
    glm::quat rotation = glm::angleAxis(deltaTime, glm::vec3(0.0f, 1.0f, 0.0f));
    m_transform->SetRotation(m_transform->GetRotation() * rotation);
}

void RendixTriangleApplication::OnRender(Engine &engine) {
    engine.GetRenderer().SetClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    engine.GetRenderer().Clear();
    engine.GetRenderer().Draw(*m_scene, *m_camera);
}

void RendixTriangleApplication::OnKey(Engine &engine, unsigned char key, bool pressed) {
    if (pressed) {
        if (key == 'w') m_camera->Move(FORWARD, m_deltaTime);
        if (key == 's') m_camera->Move(BACKWARD, m_deltaTime);
        if (key == 'a') m_camera->Move(LEFT, m_deltaTime);
        if (key == 'd') m_camera->Move(RIGHT, m_deltaTime);
    }
}

void RendixTriangleApplication::OnMouse(Engine &engine, int x, int y) {
    static bool firstMouse = true;
    static float lastX = 0.0f;
    static float lastY = 0.0f;

    if (firstMouse) {
        lastX = x;
        lastY = y;
        firstMouse = false;
    }

    float xoffset = x - lastX;
    float yoffset = lastY - y; // Reversed since y-coordinates go from bottom to top

    lastX = x;
    lastY = y;

    m_camera->Look(xoffset, yoffset);
}
