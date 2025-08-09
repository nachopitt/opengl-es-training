#ifndef RENDIX_CORE_I_WINDOW_SYSTEM_H
#define RENDIX_CORE_I_WINDOW_SYSTEM_H

#include <string>
#include <functional>
#include "events/Event.h"

namespace rendix::core
{
    class IWindowSystem
    {
    public:
        virtual ~IWindowSystem() = default;
        virtual bool CreateWindow(int width, int height, const std::string &title) = 0;
        virtual void SwapBuffers() = 0;
        virtual void PollEvents() = 0;
        virtual bool ShouldClose() = 0;
        virtual int Run() = 0;

        virtual int GetWidth() const = 0;
        virtual int GetHeight() const = 0;

        // Events
        events::Event<> onRender;
        events::Event<float /*delta*/> onUpdate;
        events::Event<int /*width*/, int /*height*/> onResize;
        events::Event<int /*key*/, bool /*pressed*/> onKey;
        events::Event<int /*x*/, int /*y*/> onMouse;
    };
}

#endif // RENDIX_CORE_I_WINDOW_SYSTEM_H
