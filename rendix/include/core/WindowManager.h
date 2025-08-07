#ifndef RENDIX_CORE_WINDOW_MANAGER_H
#define RENDIX_CORE_WINDOW_MANAGER_H

#include "esUtil.h"
#include <string>

namespace rendix::core {

    class WindowManager {
    public:
        WindowManager() = default;
        ~WindowManager() = default;

        bool CreateWindow(ESContext& ESContext, int width, int height, const std::string& title, GLuint flags);
        void SetViewPort(int width, int height);
    };
} // namespace rendix::core

#endif // RENDIX_CORE_WINDOW_MANAGER_H
