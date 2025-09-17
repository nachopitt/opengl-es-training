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
#include "shaders/GLESShaderKeywords.h"

using namespace rendix::core;
using namespace rendix::shaders;
using namespace rendix::utils;
using namespace rendix::rendering;
using namespace rendix::texturing;

RendixTriangleApplication::RendixTriangleApplication() {
    const std::string vertexShaderFile = "shaders/basic.vert";
    const std::string fragmentShaderFile = "shaders/basic.frag";

    vertexShaderDefines = {
        keywords::HasMVP,
        keywords::HasColor,
        keywords::HasTexture,
        keywords::HasLighting
    };

    fragmentShaderDefines = {
        keywords::HasColor,
        keywords::HasTexture,
        keywords::HasLighting
    };

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
    m_camera = std::make_unique<Camera>(glm::vec3(0.0f, 1.50f, 10.0f));
    m_camera->SetProjectionStrategy(std::make_unique<PerspectiveProjectionStrategy>(45.0f, 800.0f / 600.0f, 0.1f, 100.0f));

    // Initialize light
    m_light.direction = glm::vec3(0.5f, 1.0f, 0.0f);
    m_light.color = glm::vec3(1.0f, 1.0f, 1.0f);
}

void RendixTriangleApplication::SetupAttributes()
{
    shaderProgram->BindAttribute(0, "a_Position");
    shaderProgram->BindAttribute(1, "a_Color");
    shaderProgram->BindAttribute(2, "a_TexCoord");
    shaderProgram->BindAttribute(3, "a_Normal");
}

void RendixTriangleApplication::SetupScene() {
    // Create the triangle mesh
    triangleMesh = std::make_shared<GLESMesh>();
    float vertices[] = {
        // positions         // colors               //texture coordinates // normals
        // Front face
        -0.5f, -0.5f, -0.5f, 0.8f, 0.2f, 0.1f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f,
        -0.5f,  0.5f, -0.5f, 0.8f, 0.2f, 0.1f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, -1.0f,
         0.5f, -0.5f, -0.5f, 0.8f, 0.2f, 0.1f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, -1.0f,
         0.5f,  0.5f, -0.5f, 0.8f, 0.2f, 0.1f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, -1.0f,
        // Back face
        -0.5f, -0.5f,  0.5f, 0.2f, 0.8f, 0.1f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f,
        -0.5f,  0.5f,  0.5f, 0.2f, 0.8f, 0.1f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
         0.5f, -0.5f,  0.5f, 0.2f, 0.8f, 0.1f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
         0.5f,  0.5f,  0.5f, 0.2f, 0.8f, 0.1f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f,
        // Left face
        -0.5f, -0.5f, -0.5f, 0.2f, 0.1f, 0.8f, 1.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f,
        -0.5f,  0.5f, -0.5f, 0.2f, 0.1f, 0.8f, 1.0f, 0.0f, 1.0f, -1.0f, 0.0f, 0.0f,
        -0.5f, -0.5f,  0.5f, 0.2f, 0.1f, 0.8f, 1.0f, 1.0f, 0.0f, -1.0f, 0.0f, 0.0f,
        -0.5f,  0.5f,  0.5f, 0.2f, 0.1f, 0.8f, 1.0f, 1.0f, 1.0f, -1.0f, 0.0f, 0.0f,
        // Right face
         0.5f, -0.5f,  0.5f, 0.5f, 0.5f, 0.2f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
         0.5f,  0.5f,  0.5f, 0.5f, 0.5f, 0.2f, 1.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f,
         0.5f, -0.5f, -0.5f, 0.5f, 0.5f, 0.2f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f,
         0.5f,  0.5f, -0.5f, 0.5f, 0.5f, 0.2f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
        //Top face
        -0.5f,  0.5f,  0.5f, 0.2f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f,
        -0.5f,  0.5f, -0.5f, 0.2f, 0.5f, 0.5f, 1.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
         0.5f,  0.5f,  0.5f, 0.2f, 0.5f, 0.5f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
         0.5f,  0.5f, -0.5f, 0.2f, 0.5f, 0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f,
        //Bottom face
        -0.5f, -0.5f,  0.5f, 0.5f, 0.2f, 0.5f, 1.0f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f,
        -0.5f, -0.5f, -0.5f, 0.5f, 0.2f, 0.5f, 1.0f, 0.0f, 1.0f, 0.0f, -1.0f, 0.0f,
         0.5f, -0.5f,  0.5f, 0.5f, 0.2f, 0.5f, 1.0f, 1.0f, 0.0f, 0.0f, -1.0f, 0.0f,
         0.5f, -0.5f, -0.5f, 0.5f, 0.2f, 0.5f, 1.0f, 1.0f, 1.0f, 0.0f, -1.0f, 0.0f,
    };
    std::vector<uint32_t> indices = {
        // Front face
        0, 1, 2, 1, 2, 3,
        // Back face
        4, 5, 6, 5, 6, 7,
        // Left face
        8, 9, 10, 9, 10, 11,
        // Right face
        12, 13, 14, 13, 14, 15,
        // Top face
        16, 17, 18, 17, 18, 19,
        // Bottom face
        20, 21, 22, 21, 22, 23,
    };

    BufferLayout layout = {
        {ShaderDataType::Float3, "a_Position"},
        {ShaderDataType::Float4, "a_Color"},
        {ShaderDataType::Float2, "a_TexCoord"},
        {ShaderDataType::Float3, "a_Normal"}
    };

    triangleMesh->setVertices(vertices, sizeof(vertices));
    triangleMesh->setIndices(indices);
    triangleMesh->setLayout(layout);

    std::shared_ptr<rendix::texturing::ITexture> texture = rendix::texturing::ITexture::create("assets/textures/wooden-crate.jpg");

    // --- Create the Floor Mesh ---
    auto floorMesh = std::make_shared<GLESMesh>();
    float floorVertices[] = {
        // positions           // colors (white)        // texture coords // normals
        -10.0f,  0.0f,  10.0f,  1.0f, 1.0f, 1.0f, 1.0f,   0.0f,  0.0f, 0.0f, 1.0f, 0.0f,
        -10.0f,  0.0f, -10.0f,  1.0f, 1.0f, 1.0f, 1.0f,   0.0f, 10.0f, 0.0f, 1.0f, 0.0f,
         10.0f,  0.0f,  10.0f,  1.0f, 1.0f, 1.0f, 1.0f,  10.0f,  0.0f, 0.0f, 1.0f, 0.0f,
         10.0f,  0.0f, -10.0f,  1.0f, 1.0f, 1.0f, 1.0f,  10.0f, 10.0f, 0.0f, 1.0f, 0.0f
    };
    std::vector<uint32_t> floorIndices = { 0, 1, 2, 1, 2, 3 };

    // Note: The texture coordinates go from 0 to 10. This will cause your
    // texture to repeat 10 times across the floor. If you want the texture
    // to stretch, use UVs from 0.0 to 1.0 instead.

    BufferLayout floorLayout = {
        {ShaderDataType::Float3, "a_Position"},
        {ShaderDataType::Float4, "a_Color"},
        {ShaderDataType::Float2, "a_TexCoord"},
        {ShaderDataType::Float3, "a_Normal"}
    };

    floorMesh->setVertices(floorVertices, sizeof(floorVertices));
    floorMesh->setIndices(floorIndices);
    floorMesh->setLayout(floorLayout);

    // --- Create the Floor Scene Object ---
    auto floorTransform = std::make_shared<Transform>();
    floorTransform->SetPosition(glm::vec3(0.0f, -1.0f, 0.0f));

    // You might want a different texture for the floor
    std::shared_ptr<rendix::texturing::ITexture> floorTexture = rendix::texturing::ITexture::create("assets/textures/paving-stones.png");

    auto floorObject = SceneObject::CreateBuilder()
        .WithMesh(floorMesh)
        .WithShaderProgram(shaderProgram) // You can use the same shader program
        .WithTexture(floorTexture)
        .WithTransform(floorTransform)
        .Build();

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
    m_scene->AddObject(floorObject);
}

void RendixTriangleApplication::OnUpdate(Engine &engine, float deltaTime) {
    Application::OnUpdate(engine, deltaTime);
    // Rotate the box
    glm::quat rotation = glm::angleAxis(deltaTime, glm::vec3(0.0f, 1.0f, 0.0f));
    m_transform->SetRotation(m_transform->GetRotation() * rotation);
}

void RendixTriangleApplication::OnRender(Engine &engine) {
    engine.GetRenderer().SetClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    engine.GetRenderer().Clear();

    shaderProgram->Use();
    shaderProgram->SetUniform("u_LightDirection", m_light.direction);
    shaderProgram->SetUniform("u_LightColor", m_light.color);

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

void RendixTriangleApplication::OnWindowResize(rendix::core::Engine &engine, int width, int height)
{
    engine.GetRenderer().Resize(width, height);
}
