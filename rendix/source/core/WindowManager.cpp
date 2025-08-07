#include "core/WindowManager.h"
#include <string>
#include "esUtil.h"

namespace rendix::core {

    bool WindowManager::CreateWindow(ESContext& esContext, int width, int height, const std::string& title, GLuint flags) {
        return esCreateWindow(&esContext, title.c_str(), width, height, flags);
    }

    void WindowManager::SetViewPort(int width, int height) {
        glViewport(0, 0, width, height);
    }
}
