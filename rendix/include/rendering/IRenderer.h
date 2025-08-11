#ifndef RENDIX_RENDERING_I_RENDERER_H
#define RENDIX_RENDERING_I_RENDERER_H

#include "rendering/Mesh.h"
#include "shaders/ShaderProgram.h"
#include "texturing/Texture.h"

namespace rendix::rendering {

    class IRenderer {
    public:
        IRenderer(int width, int height) : width(width), height(height) { }
        virtual ~IRenderer() = default;

        // Initialize renderer.
        virtual void Init() = 0;
        // Draw mesh with a specific shader and texture.
        virtual void Draw(Mesh &mesh, shaders::ShaderProgram &shaderProgram, texturing::Texture &texture) = 0;
        // Set background clear color.
        virtual void SetClearColor(float r, float g, float b, float a) = 0;
        // Clear screen.
        virtual void Clear() = 0;
        // Resize screen
        virtual void Resize(int width, int height) = 0;

    protected:
        int width;
        int height;
    };
}

#endif //RENDIX_RENDERING_I_RENDERER_H
