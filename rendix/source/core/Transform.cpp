
#include "core/Transform.h"
#include <glm/gtc/matrix_transform.hpp>

namespace rendix::core {

Transform::Transform()
    : m_position(0.0f, 0.0f, 0.0f),
      m_rotation(1.0f, 0.0f, 0.0f, 0.0f),
      m_scale(1.0f, 1.0f, 1.0f) {}

void Transform::SetPosition(const glm::vec3& position) {
    m_position = position;
}

void Transform::SetRotation(const glm::quat& rotation) {
    m_rotation = rotation;
}

void Transform::SetScale(const glm::vec3& scale) {
    m_scale = scale;
}

const glm::vec3& Transform::GetPosition() const {
    return m_position;
}

const glm::quat& Transform::GetRotation() const {
    return m_rotation;
}

const glm::vec3& Transform::GetScale() const {
    return m_scale;
}

glm::mat4 Transform::GetModelMatrix() const {
    glm::mat4 model = glm::translate(glm::mat4(1.0f), m_position);
    model *= glm::mat4_cast(m_rotation);
    model = glm::scale(model, m_scale);
    return model;
}

} // namespace rendix::core
