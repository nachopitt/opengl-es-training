
#ifndef RENDIX_CORE_CAMERA_H
#define RENDIX_CORE_CAMERA_H

#include <glm/glm.hpp>
#include <memory>

#include "rendering/IProjectionStrategy.h"

namespace rendix::core {

// Defines several possible directions for camera movement.
enum CameraDirection {
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT
};

// Default camera values
const float CAMERA_DEFAULT_YAW         = -90.0f;
const float CAMERA_DEFAULT_PITCH       = 0.0f;
const float CAMERA_DEFAULT_SPEED       = 2.5f;
const float CAMERA_DEFAULT_SENSITIVITY = 0.1f;
const float CAMERA_DEFAULT_ZOOM        = 45.0f;

class Camera {
public:
    // camera Attributes
    glm::vec3 Position;
    glm::vec3 Front;
    glm::vec3 Up;
    glm::vec3 Right;
    glm::vec3 WorldUp;
    // euler Angles
    float Yaw;
    float Pitch;
    // camera options
    float MovementSpeed;
    float MouseSensitivity;
    float Zoom;

    // projection strategy
    std::unique_ptr<rendix::rendering::IProjectionStrategy> m_projectionStrategy;

    // constructor with vectors
    Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), float yaw = CAMERA_DEFAULT_YAW, float pitch = CAMERA_DEFAULT_PITCH);
    // constructor with scalar values
    Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch);

    // returns the view matrix calculated using Euler Angles and the LookAt Matrix
    glm::mat4 GetViewMatrix() const;

    // returns the projection matrix from the current strategy
    glm::mat4 GetProjectionMatrix() const;

    // Processes movement commands. Accepts a direction and a delta time.
    void Move(CameraDirection direction, float deltaTime);

    // Processes look commands. Expects x and y offsets for yaw and pitch changes.
    void Look(float xoffset, float yoffset, bool constrainPitch = true);

    // Processes zoom commands. Expects a zoom offset.
    void ChangeZoom(float yoffset);

    void SetProjectionStrategy(std::unique_ptr<rendix::rendering::IProjectionStrategy> strategy);

private:
    // calculates the front vector from the Camera's (updated) Euler Angles
    void updateCameraVectors();
};

} // namespace rendix::core

#endif // RENDIX_CORE_CAMERA_H
