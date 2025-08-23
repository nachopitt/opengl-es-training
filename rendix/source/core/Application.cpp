#include "core/Application.h"
#include <iostream>
#include "core/Engine.h"
#include "rendering/GLESMesh.h" // For default mesh
#include "rendering/Scene.h" // For default scene
#include "rendering/Vertex.h" // For BufferLayout
#include <memory> // For std::make_shared

namespace rendix::core {

    Application::Application() : m_scene(std::make_shared<rendering::Scene>())
    {
        vertexShaderStr = R"(
attribute vec4 position;
void main()
{
   gl_Position = position;
})";
        fragmentShaderStr = R"(
void main()
{
   gl_FragColor = vec4(1.0, 1.0, 1.0, 1.0);
})";
    }

    void Application::OnInit(Engine &engine)
    {
        std::cout << "Application OnInit" << std::endl;

        SetupShaders();
        SetupScene();
    }

    void Application::OnRender(Engine &engine)
    {
        engine.GetRenderer().SetClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        engine.GetRenderer().Clear();

        engine.GetRenderer().Draw(*m_scene);
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
        std::cout << "Application OnKey: key: " << static_cast<int>(key) << ", pressed: "  << pressed << std::endl;
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

    void Application::SetupShaders()
    {
        vertexShader = std::make_shared<shaders::GLESShader>(shaders::ShaderType::VERTEX);
        fragmentShader = std::make_shared<shaders::GLESShader>(shaders::ShaderType::FRAGMENT);
        shaderProgram = std::make_shared<shaders::GLESShaderProgram>();

        if (!vertexShader->Compile(vertexShaderStr))
        {
            std::cerr << "Error compiling vertex shader" << std::endl;
        }
        if (!fragmentShader->Compile(fragmentShaderStr))
        {
            std::cerr << "Error compiling fragment shader" << std::endl;
        }

        if (!shaderProgram->AttachShader(*vertexShader))
        {
            std::cerr << "Error attaching vertex shader to shader program" << std::endl;
        }
        if (!shaderProgram->AttachShader(*fragmentShader))
        {
            std::cerr << "Error attaching fragment shader to shader program" << std::endl;
        }

        SetupAttributes();

        if (!shaderProgram->LinkShaders())
        {
            std::cerr << "Error linking vertex and fragment shaders into the shader program" << std::endl;
        }
    }

    void Application::SetupAttributes()
    {
        shaderProgram->BindAttribute(0, "position");
    }

    void Application::SetupScene()
    {
        // Create the default white rectangle mesh
        float vertices[] = {
            -0.5f, -0.5f, 0.0f, // Bottom-left
            -0.5f, 0.5f, 0.0f,  // Top-left
            0.5f, -0.5f, 0.0f,  // Bottom-right
            0.5f, 0.5f, 0.0f    // Top-right
        };
        std::vector<uint32_t> indices = {
            0, 1, 2, // First triangle
            1, 3, 2  // Second triangle
        };

        rendering::BufferLayout layout = {
            {rendering::ShaderDataType::Float3, "position"}};

        std::shared_ptr<rendering::GLESMesh> defaultMesh = std::make_shared<rendering::GLESMesh>();
        defaultMesh->setVertices(vertices, sizeof(vertices));
        defaultMesh->setIndices(indices);
        defaultMesh->setLayout(layout);

        // Create scene and add the default mesh
        m_scene = std::make_shared<rendering::Scene>();
        m_scene->AddObject(defaultMesh, shaderProgram);
    }
}
