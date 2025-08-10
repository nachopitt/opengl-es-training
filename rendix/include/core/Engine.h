#ifndef RENDIX_CORE_ENGINE
#define RENDIX_CORE_ENGINE

#include <string>

#include "esUtil.h"
#include "core/Application.h"
#include "core/IWindowSystem.h"
#include <memory>

namespace rendix::core
{
    class Engine
    {
    public:
        Engine(IWindowSystem *windowSystem);
        Engine(IWindowSystem *windowSystem, std::unique_ptr<Application> application);
        ~Engine() = default;
        bool Init(int width, int height, const std::string &windowTitleName);
        void Run();

        // Events
        events::Event<> onInit;
        events::Event<> onShutdown;

    protected:
        IWindowSystem *windowSystem;
        std::unique_ptr<Application> application;
    };
}

#endif // RENDIX_CORE_ENGINE
