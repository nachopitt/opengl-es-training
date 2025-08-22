#include "rendering/GLESRenderer.h"
#include "rendering/GLESMesh.h"
#include "shaders/IShaderProgram.h"
#include "texturing/GLESTexture.h"
#include "esUtil.h"
#include "rendering/IScene.h"

namespace rendix::rendering {

    using namespace shaders;
    using namespace texturing;

    void GLESRenderer::Init()
    {
    }

    GLESRenderer::GLESRenderer(int width, int height) : IRenderer(width, height)
    {
    }

    void GLESRenderer::Draw(IScene &scene)
    {
        for (const auto& object : scene.GetObjects()) {
            object.shaderProgram->Use();
            object.mesh->Bind(*object.shaderProgram);

            if (object.texture) {
                object.texture->bind(0); // Bind to texture unit 0
                object.shaderProgram->SetUniform("u_Texture", 0); // Set uniform to texture unit 0
            }

            // TODO: Set model matrix uniform
            // object.shaderProgram->SetUniform("u_ModelMatrix", object.modelMatrix);

            glDrawElements(GL_TRIANGLES, object.mesh->getIndexCount(), GL_UNSIGNED_INT, 0);

            if (object.texture) {
                object.texture->unbind();
            }

            object.mesh->Unbind();
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
