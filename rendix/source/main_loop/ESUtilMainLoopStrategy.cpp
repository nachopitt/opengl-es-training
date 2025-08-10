#include "main_loop/ESUtilMainLoopStrategy.h"
#include "core/ESUtilWindowSystem.h"
#include "esUtil.h"

namespace rendix::main_loop {

    void ESUtilMainLoopStrategy::Run(core::IWindowSystem &windowSystem)
    {
        core::ESUtilWindowSystem &esUtilWindowSystem = static_cast<core::ESUtilWindowSystem &>(windowSystem);

        esMainLoop(&esUtilWindowSystem.GetContext());
    }
}
