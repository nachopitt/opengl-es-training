#ifndef RENDIX_TRIANGLE_APPLICATION_H
#define RENDIX_TRIANGLE_APPLICATION_H

#include "core/Application.h"

class RendixTriangleApplication : public rendix::core::Application {
public:
    RendixTriangleApplication() = default;
    ~RendixTriangleApplication() = default;

    virtual void OnDraw() const override;
    virtual void OnKey(unsigned char key, int x, int y) const override;
    virtual void OnUpdate(float deltaTime) const override;
    virtual void OnWindowResize(int width, int height) const override;
};

#endif // RENDIX_TRIANGLE_APPLICATION_H
