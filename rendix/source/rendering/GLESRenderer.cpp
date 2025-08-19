#include "rendering/GLESRenderer.h"
#include "rendering/Mesh.h"
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

    void GLESRenderer::Draw(Mesh &mesh, IShaderProgram &shader)
    {
        shader.Use();

        const auto& vertices = mesh.getVertices();
        const auto& indices = mesh.getIndices();

        GLint positionLoc = shader.GetAttributeLocation("vPosition");
        GLint colorLoc = shader.GetAttributeLocation("aColor");

        if (positionLoc != -1) {
            glVertexAttribPointer(positionLoc, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), &vertices[0].position);
            glEnableVertexAttribArray(positionLoc);
        }

        if (colorLoc != -1) {
            glVertexAttribPointer(colorLoc, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), &vertices[0].color);
            glEnableVertexAttribArray(colorLoc);
        }

        glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, indices.data());

        if (positionLoc != -1) {
            glDisableVertexAttribArray(positionLoc);
        }
        if (colorLoc != -1) {
            glDisableVertexAttribArray(colorLoc);
        }
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
