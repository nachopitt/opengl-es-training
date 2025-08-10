#ifndef RENDIX_CORE_APPLICATION_H
#define RENDIX_CORE_APPLICATION_H

namespace rendix::core {

    class Engine;

    class Application {
    public:
        virtual ~Application() = default;

        virtual void OnInit(Engine &engine) const;
        virtual void OnRender(Engine &engine) const;
        virtual void OnUpdate(Engine &engine, float deltaTime) const;
        virtual void OnKey(Engine &engine, unsigned char key, bool pressed) const;
        virtual void OnMouse(Engine &engine, int x, int y) const;
        virtual void OnWindowResize(Engine &engine, int width, int height) const;
        virtual void OnShutdown(Engine &engine) const;
    };

} // namespace rendix::rendering

#endif //RENDIX_CORE_APPLICATION_H
