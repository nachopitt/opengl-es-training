
#ifndef RENDIX_RENDERING_PERSPECTIVEPROJECTIONSTRATEGY_H
#define RENDIX_RENDERING_PERSPECTIVEPROJECTIONSTRATEGY_H

#include "rendering/IProjectionStrategy.h"

namespace rendix::rendering {

class PerspectiveProjectionStrategy : public IProjectionStrategy {
public:
    PerspectiveProjectionStrategy(float fov, float aspectRatio, float nearPlane, float farPlane);
    ~PerspectiveProjectionStrategy() = default;

    glm::mat4 GetProjectionMatrix() const override;

    void SetFOV(float fov);
    void SetAspectRatio(float aspectRatio);
    void SetNearPlane(float nearPlane);
    void SetFarPlane(float farPlane);

    float GetFOV() const;
    float GetAspectRatio() const;
    float GetNearPlane() const;
    float GetFarPlane() const;

private:
    float m_fov;
    float m_aspectRatio;
    float m_nearPlane;
    float m_farPlane;
};

} // namespace rendix::rendering

#endif // RENDIX_RENDERING_PERSPECTIVEPROJECTIONSTRATEGY_H
