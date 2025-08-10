#ifndef RENDIX_CORE_ES_UTIL_WINDOW_SYSTEM_H
#define RENDIX_CORE_ES_UTIL_WINDOW_SYSTEM_H

#include "core/IWindowSystem.h"
#include "esUtil.h"
#include <string>

namespace rendix::core {

    class ESUtilWindowSystem : public IWindowSystem
    {
    public:
        ESUtilWindowSystem();
        ~ESUtilWindowSystem() = default;

        bool CreateWindow(int width, int height, const std::string &title) override;
        void SwapBuffers() override;
        void PollEvents() override;
        bool ShouldClose() override;
        std::unique_ptr<main_loop::IMainLoopStrategy> GetMainLoop() override;

        int GetWidth() const override;
        int GetHeight() const override;

        ESContext& GetContext();

        static void OnDraw(ESContext *esContext);
        static void OnKey(ESContext *esContext, unsigned char key, int x, int y);
        static void OnUpdate(ESContext *esContext, float deltaTime);
        static void OnWindowResize(ESContext *esContext, int width, int height);

    private:
        ESContext esContext;
        bool shouldClose;
    };
} // namespace rendix::core

#endif // RENDIX_CORE_ES_UTIL_WINDOW_SYSTEM_H
