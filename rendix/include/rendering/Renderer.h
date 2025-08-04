#ifndef RENDIX_RENDERING_RENDERER_H
#define RENDIX_RENDERING_RENDERER_H

#include "esUtil.h"
#include "rendering/Mesh.h"
#include "shaders/ShaderProgram.h"
#include "texturing/Texture.h"

namespace rendix::rendering
{
    class Renderer
    {
        public:
            Renderer(GLint width, GLint height);
            ~Renderer();
            // Initialize OpenGL and other settings.
            void Init();
            // Draw mesh with a specific shader and texture.
            void Draw(Mesh &mesh, shaders::ShaderProgram &shaderProgram, texturing::Texture &texture);
            // Set background clear color.
            void SetClearColor(float r, float g, float b, float a);
            // Clear screen.
            void Clear();
    };
}

#endif // RENDIX_RENDERING_RENDERER_H
