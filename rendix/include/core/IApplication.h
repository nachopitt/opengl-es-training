#ifndef RENDIX_CORE_I_APPLICATION_H
#define RENDIX_CORE_I_APPLICATION_H

namespace rendix::core {

    class Engine;

    class IApplication {
    public:
        virtual ~IApplication() = default;
        virtual void OnInit(Engine &engine) = 0;
        virtual void OnRender(Engine &engine) = 0;
        virtual void OnUpdate(Engine &engine, float deltaTime) = 0;
        virtual void OnKey(Engine &engine, unsigned char key, bool pressed) = 0;
        virtual void OnMouse(Engine &engine, int x, int y) = 0;
        virtual void OnWindowResize(Engine &engine, int width, int height) = 0;
        virtual void OnShutdown(Engine &engine) = 0;
    };
}

#endif //RENDIX_CORE_I_APPLICATION_H
