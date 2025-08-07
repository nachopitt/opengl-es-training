#ifndef RENDIX_CORE_ENGINE
#define RENDIX_CORE_ENGINE

#include <string>

#include "esUtil.h"
#include "core/Application.h"
#include "core/WindowManager.h"

namespace rendix::core
{
    class Engine
    {
    public:
        Engine();
        ~Engine() = default;
        bool Init(GLint width, GLint height, const std::string &windowTitleName, GLuint flags);
        void SetApplication(Application *application);
        int Run();

        static void OnDraw(ESContext *esContext);
        static void OnKey(ESContext *esContext, unsigned char key, int x, int y);
        static void OnUpdate(ESContext *esContext, float deltaTime);
        static void OnWindowResize(ESContext *esContext, int width, int height);

    protected:
        ESContext esContext;
        WindowManager windowManager;
        Application *application;
    };
}

#endif // RENDIX_CORE_ENGINE
