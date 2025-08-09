#include "rendering/Renderer.h"
#include "rendering/Mesh.h"
#include "shaders/ShaderProgram.h"
#include "texturing/Texture.h"
#include "esUtil.h"

namespace rendix::rendering {

    using namespace shaders;
    using namespace texturing;

    Renderer::Renderer(GLint width, GLint height)
    {
        // Initialization code, if needed
    }

    void Renderer::Draw(Mesh &mesh, ShaderProgram &shader, Texture &texture)
    {
        // Drawing code, e.g., glDrawArrays or glDrawElements
        // This is a placeholder; actual implementation depends on your rendering pipeline
    }

    void Renderer::SetClearColor(float r, float g, float b, float a) {
        glClearColor(r, g, b, a);
    }

    void Renderer::Clear()
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    void Renderer::Resize(int width, int height)
    {
        glViewport(0, 0, width, height);
    }
}
