#ifndef RENDIX_MAIN_LOOP_ES_UTIL_MAIN_LOOP_STRATEGY
#define RENDIX_MAIN_LOOP_ES_UTIL_MAIN_LOOP_STRATEGY

#include "main_loop/IMainLoopStrategy.h"

namespace rendix::main_loop {

    class ESUtilMainLoopStrategy : public IMainLoopStrategy
    {
    public:
        void Run(core::IWindowSystem &windowSystem) override;
    };
}

#endif //RENDIX_MAIN_LOOP_ES_UTIL_MAIN_LOOP_STRATEGY
