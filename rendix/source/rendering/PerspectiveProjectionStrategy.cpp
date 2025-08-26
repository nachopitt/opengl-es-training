
#include "rendering/PerspectiveProjectionStrategy.h"
#include <glm/gtc/matrix_transform.hpp>

namespace rendix::rendering {

PerspectiveProjectionStrategy::PerspectiveProjectionStrategy(float fov, float aspectRatio, float nearPlane, float farPlane)
    : m_fov(fov),
      m_aspectRatio(aspectRatio),
      m_nearPlane(nearPlane),
      m_farPlane(farPlane) {}

glm::mat4 PerspectiveProjectionStrategy::GetProjectionMatrix() const {
    return glm::perspective(glm::radians(m_fov), m_aspectRatio, m_nearPlane, m_farPlane);
}

void PerspectiveProjectionStrategy::SetFOV(float fov) {
    m_fov = fov;
}

void PerspectiveProjectionStrategy::SetAspectRatio(float aspectRatio) {
    m_aspectRatio = aspectRatio;
}

void PerspectiveProjectionStrategy::SetNearPlane(float nearPlane) {
    m_nearPlane = nearPlane;
}

void PerspectiveProjectionStrategy::SetFarPlane(float farPlane) {
    m_farPlane = farPlane;
}

float PerspectiveProjectionStrategy::GetFOV() const {
    return m_fov;
}

float PerspectiveProjectionStrategy::GetAspectRatio() const {
    return m_aspectRatio;
}

float PerspectiveProjectionStrategy::GetNearPlane() const {
    return m_nearPlane;
}

float PerspectiveProjectionStrategy::GetFarPlane() const {
    return m_farPlane;
}

} // namespace rendix::rendering
