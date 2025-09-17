#ifndef RENDIX_RENDERING_LIGHT_H
#define RENDIX_RENDERING_LIGHT_H

#include <glm/glm.hpp>

namespace rendix::rendering {

struct DirectionalLight {
    glm::vec3 direction;
    glm::vec3 color;
};

} // namespace rendix::rendering

#endif //RENDIX_RENDERING_LIGHT_H
