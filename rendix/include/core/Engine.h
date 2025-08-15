#ifndef RENDIX_CORE_ENGINE_H
#define RENDIX_CORE_ENGINE_H

#include <string>

#include "esUtil.h"
#include "core/IApplication.h"
#include "core/IWindowSystem.h"
#include "rendering/IRenderer.h"
#include <memory>

namespace rendix::core
{
    class Engine
    {
    public:
        Engine(IWindowSystem *windowSystem, rendering::IRenderer *renderer);
        Engine(IWindowSystem *windowSystem, rendering::IRenderer *renderer, IApplication *application);
        ~Engine() = default;
        bool Init();
        void Run();
        IWindowSystem &GetWindowSystem() const;
        rendering::IRenderer &GetRenderer() const;

        // Events
        events::Event<> onInit;
        events::Event<> onShutdown;

    protected:
        IWindowSystem *windowSystem;
        rendering::IRenderer *renderer;
        IApplication* application;
    };
}

#endif // RENDIX_CORE_ENGINE_H
