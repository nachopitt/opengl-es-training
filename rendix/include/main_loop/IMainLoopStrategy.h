#ifndef RENDIX_MAIN_LOOP_I_MAIN_LOOP_STRATEGY_H
#define RENDIX_MAIN_LOOP_I_MAIN_LOOP_STRATEGY_H

namespace rendix::core
{
    class IWindowSystem;
}

namespace rendix::main_loop {

    class IMainLoopStrategy {
    public:
        virtual ~IMainLoopStrategy() = default;
        virtual void Run(rendix::core::IWindowSystem &windowSystem) = 0;
    };
}

#endif //RENDIX_MAIN_LOOP_I_MAIN_LOOP_STRATEGY_H
