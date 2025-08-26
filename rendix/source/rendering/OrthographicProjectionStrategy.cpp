
#include "rendering/OrthographicProjectionStrategy.h"
#include <glm/gtc/matrix_transform.hpp>

namespace rendix::rendering {

OrthographicProjectionStrategy::OrthographicProjectionStrategy(float left, float right, float bottom, float top, float nearPlane, float farPlane)
    : m_left(left),
      m_right(right),
      m_bottom(bottom),
      m_top(top),
      m_nearPlane(nearPlane),
      m_farPlane(farPlane) {}

glm::mat4 OrthographicProjectionStrategy::GetProjectionMatrix() const {
    return glm::ortho(m_left, m_right, m_bottom, m_top, m_nearPlane, m_farPlane);
}

void OrthographicProjectionStrategy::SetBounds(float left, float right, float bottom, float top) {
    m_left = left;
    m_right = right;
    m_bottom = bottom;
    m_top = top;
}

void OrthographicProjectionStrategy::SetNearPlane(float nearPlane) {
    m_nearPlane = nearPlane;
}

void OrthographicProjectionStrategy::SetFarPlane(float farPlane) {
    m_farPlane = farPlane;
}

float OrthographicProjectionStrategy::GetLeft() const {
    return m_left;
}

float OrthographicProjectionStrategy::GetRight() const {
    return m_right;
}

float OrthographicProjectionStrategy::GetBottom() const {
    return m_bottom;
}

float OrthographicProjectionStrategy::GetTop() const {
    return m_top;
}

float OrthographicProjectionStrategy::GetNearPlane() const {
    return m_nearPlane;
}

float OrthographicProjectionStrategy::GetFarPlane() const {
    return m_farPlane;
}

} // namespace rendix::rendering
