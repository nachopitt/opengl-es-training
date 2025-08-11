#include "rendering/OpenGLESRenderer.h"
#include "rendering/Mesh.h"
#include "shaders/ShaderProgram.h"
#include "texturing/Texture.h"
#include "esUtil.h"

namespace rendix::rendering {

    using namespace shaders;
    using namespace texturing;

    void OpenGLESRenderer::Init()
    {
    }

    OpenGLESRenderer::OpenGLESRenderer(int width, int height) : IRenderer(width, height)
    {
    }

    void OpenGLESRenderer::Draw(Mesh &mesh, ShaderProgram &shader, Texture &texture)
    {
        // Drawing code, e.g., glDrawArrays or glDrawElements
        // This is a placeholder; actual implementation depends on your rendering pipeline
    }

    void OpenGLESRenderer::SetClearColor(float r, float g, float b, float a) {
        glClearColor(r, g, b, a);
    }

    void OpenGLESRenderer::Clear()
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    void OpenGLESRenderer::Resize(int width, int height)
    {
        glViewport(0, 0, width, height);
    }
}
