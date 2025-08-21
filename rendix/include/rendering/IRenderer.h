#ifndef RENDIX_RENDERING_I_RENDERER_H
#define RENDIX_RENDERING_I_RENDERER_H

#include "rendering/IMesh.h"
#include "shaders/IShaderProgram.h"
#include "texturing/Texture.h"
#include "rendering/IScene.h"

namespace rendix::rendering {

    class IRenderer {
    public:
        IRenderer(int width, int height) : width(width), height(height) { }
        virtual ~IRenderer() = default;

        // Initialize renderer.
        virtual void Init() = 0;
        // Draw a scene.
        virtual void Draw(IScene &scene) = 0;
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
