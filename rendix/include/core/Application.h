#ifndef RENDIX_CORE_APPLICATION_H
#define RENDIX_CORE_APPLICATION_H

#include "esUtil.h"

namespace rendix::core {

    class Application {
    public:
        virtual ~Application() = default;

        virtual void OnDraw() const;
        virtual void OnKey(unsigned char key, int x, int y) const;
        virtual void OnUpdate(float deltaTime) const;
        virtual void OnWindowResize(int width, int height) const;
    };

} // namespace rendix::rendering

#endif //RENDIX_CORE_APPLICATION_H
