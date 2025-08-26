
#ifndef RENDIX_CORE_TRANSFORM_H
#define RENDIX_CORE_TRANSFORM_H

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

namespace rendix::core {

class Transform {
public:
    Transform();
    ~Transform() = default;

    void SetPosition(const glm::vec3& position);
    void SetRotation(const glm::quat& rotation);
    void SetScale(const glm::vec3& scale);

    const glm::vec3& GetPosition() const;
    const glm::quat& GetRotation() const;
    const glm::vec3& GetScale() const;

    glm::mat4 GetModelMatrix() const;

private:
    glm::vec3 m_position;
    glm::quat m_rotation;
    glm::vec3 m_scale;
};

} // namespace rendix::core

#endif // RENDIX_CORE_TRANSFORM_H
