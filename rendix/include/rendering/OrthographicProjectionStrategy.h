
#ifndef RENDIX_RENDERING_ORTHOGRAPHICPROJECTIONSTRATEGY_H
#define RENDIX_RENDERING_ORTHOGRAPHICPROJECTIONSTRATEGY_H

#include "rendering/IProjectionStrategy.h"

namespace rendix::rendering {

class OrthographicProjectionStrategy : public IProjectionStrategy {
public:
    OrthographicProjectionStrategy(float left, float right, float bottom, float top, float nearPlane, float farPlane);
    ~OrthographicProjectionStrategy() = default;

    glm::mat4 GetProjectionMatrix() const override;

    void SetBounds(float left, float right, float bottom, float top);
    void SetNearPlane(float nearPlane);
    void SetFarPlane(float farPlane);

    float GetLeft() const;
    float GetRight() const;
    float GetBottom() const;
    float GetTop() const;
    float GetNearPlane() const;
    float GetFarPlane() const;

private:
    float m_left;
    float m_right;
    float m_bottom;
    float m_top;
    float m_nearPlane;
    float m_farPlane;
};

} // namespace rendix::rendering

#endif // RENDIX_RENDERING_ORTHOGRAPHICPROJECTIONSTRATEGY_H
