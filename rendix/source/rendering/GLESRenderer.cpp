#include "rendering/GLESRenderer.h"
#include "rendering/GLESMesh.h"
#include "shaders/IShaderProgram.h"
#include "texturing/Texture.h"
#include "esUtil.h"

namespace rendix::rendering {

    using namespace shaders;
    using namespace texturing;

    void GLESRenderer::Init()
    {
    }

    GLESRenderer::GLESRenderer(int width, int height) : IRenderer(width, height)
    {
    }

    void GLESRenderer::Draw(IMesh &mesh, IShaderProgram &shaderProgram)
    {
        shaderProgram.Use();
        mesh.Bind(shaderProgram);

        glDrawElements(GL_TRIANGLES, mesh.getIndexCount(), GL_UNSIGNED_INT, 0);

        // The attributes are disabled in the mesh.Unbind() method
        mesh.Unbind();
    }

    void GLESRenderer::SetClearColor(float r, float g, float b, float a) {
        glClearColor(r, g, b, a);
    }

    void GLESRenderer::Clear()
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    void GLESRenderer::Resize(int width, int height)
    {
        glViewport(0, 0, width, height);
    }
}
