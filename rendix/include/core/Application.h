#ifndef RENDIX_CORE_APPLICATION_H
#define RENDIX_CORE_APPLICATION_H

#include "esUtil.h"

namespace rendix::core {

    class Application {
    public:
        virtual ~Application() = default;

        virtual void OnDraw(ESContext *ESContext) const = 0;
        virtual void OnKey(ESContext *ESContext, unsigned char key, int x, int y) const = 0;
        virtual void OnUpdate(ESContext *ESContext, float deltaTime) const = 0;
        virtual void OnWindowResize(ESContext *ESContext, int width, int height) const = 0;
    };

} // namespace rendix::rendering

#endif //RENDIX_CORE_APPLICATION_H
