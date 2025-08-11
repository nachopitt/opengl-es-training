#ifndef RENDIX_CORE_APPLICATION_H
#define RENDIX_CORE_APPLICATION_H

namespace rendix::core {

    class Engine;

    class Application {
    public:
        virtual ~Application() = default;

        virtual void OnInit(Engine &engine);
        virtual void OnRender(Engine &engine);
        virtual void OnUpdate(Engine &engine, float deltaTime);
        virtual void OnKey(Engine &engine, unsigned char key, bool pressed);
        virtual void OnMouse(Engine &engine, int x, int y);
        virtual void OnWindowResize(Engine &engine, int width, int height);
        virtual void OnShutdown(Engine &engine);
    };

} // namespace rendix::rendering

#endif //RENDIX_CORE_APPLICATION_H
