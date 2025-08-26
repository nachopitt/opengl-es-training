
#ifndef RENDIX_RENDERING_IPROJECTIONSTRATEGY_H
#define RENDIX_RENDERING_IPROJECTIONSTRATEGY_H

#include <glm/glm.hpp>

namespace rendix::rendering {

class IProjectionStrategy {
public:
    virtual ~IProjectionStrategy() = default;
    virtual glm::mat4 GetProjectionMatrix() const = 0;
};

} // namespace rendix::rendering

#endif // RENDIX_RENDERING_IPROJECTIONSTRATEGY_H
