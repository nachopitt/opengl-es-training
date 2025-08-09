#include "shaders/Shader.h"
#include "shaders/ShaderProgram.h"
#include "core/Engine.h"
#include "core/ESUtilWindowSystem.h"

int main(int argc, char* argv[])
{
    rendix::core::ESUtilWindowSystem windowSystem;
    rendix::core::Engine engine(&windowSystem);
    rendix::shaders::Shader vertexShader(GL_VERTEX_SHADER);
    rendix::shaders::Shader fragmentShader(GL_FRAGMENT_SHADER);
    rendix::shaders::ShaderProgram shaderProgram;

    vertexShader.LoadFromFile("shaders/basic-color.vs");
    fragmentShader.LoadFromFile("shaders/basic.fs");

    vertexShader.Compile();
    fragmentShader.Compile();

    shaderProgram.AttachShader(vertexShader);
    shaderProgram.AttachShader(fragmentShader);

    shaderProgram.LinkShaders();

    engine.Init(640, 480, "Rendix Triangle OpenGL ES example");

    return engine.Run();
}
