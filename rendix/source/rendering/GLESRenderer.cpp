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

    void GLESRenderer::Draw(IMesh &mesh, IShaderProgram &shader)
    {
        shader.Use();

        auto& glesMesh = static_cast<GLESMesh&>(mesh);

        glBindBuffer(GL_ARRAY_BUFFER, glesMesh.getVBO());
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, glesMesh.getIBO());

        const auto& indices = glesMesh.getIndices();

        GLint positionLoc = shader.GetAttributeLocation("vPosition");
        GLint colorLoc = shader.GetAttributeLocation("aColor");

        if (positionLoc != -1) {
            glVertexAttribPointer(positionLoc, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)offsetof(Vertex, position));
            glEnableVertexAttribArray(positionLoc);
        }

        if (colorLoc != -1) {
            glVertexAttribPointer(colorLoc, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)offsetof(Vertex, color));
            glEnableVertexAttribArray(colorLoc);
        }

        glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);

        if (positionLoc != -1) {
            glDisableVertexAttribArray(positionLoc);
        }
        if (colorLoc != -1) {
            glDisableVertexAttribArray(colorLoc);
        }

        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
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
