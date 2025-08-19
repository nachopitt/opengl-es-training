#ifndef RENDIX_CORE_RENDIX_EXCEPTION_H
#define RENDIX_CORE_RENDIX_EXCEPTION_H

#include <stdexcept>
#include <string>

namespace rendix::core {

class RendixException : public std::runtime_error {
public:
    explicit RendixException(const std::string& message)
        : std::runtime_error(message) {}

    explicit RendixException(const char* message)
        : std::runtime_error(message) {}
};

} // namespace rendix::core

#endif // RENDIX_CORE_RENDIX_EXCEPTION_H
