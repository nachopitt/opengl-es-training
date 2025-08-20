#ifndef RENDIX_RENDERING_GLES_RENDERER_H
#define RENDIX_RENDERING_GLES_RENDERER_H

#include "rendering/IRenderer.h"
#include "rendering/IMesh.h"
#include "shaders/IShaderProgram.h"
#include "texturing/Texture.h"

namespace rendix::rendering
{

    class GLESRenderer: public IRenderer
    {
        public:
            GLESRenderer(int width, int height);
            // Initialize OpenGL and other settings.
            void Init() override;
            // Draw mesh with a specific shader.
            void Draw(IMesh &mesh, shaders::IShaderProgram &shaderProgram) override;
            // Set background clear color.
            void SetClearColor(float r, float g, float b, float a) override;
            // Clear screen.
            void Clear() override;
            // Resize screen
            void Resize(int width, int height) override;
    };
}

#endif // RENDIX_RENDERING_GLES_RENDERER_H
