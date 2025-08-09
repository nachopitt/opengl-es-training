#ifndef RENDIX_EVENTS_EVENT
#define RENDIX_EVENTS_EVENT

#include <vector>
#include <functional>

namespace rendix::events {

    template <typename... Args>
    class Event
    {
    public:
        using Handler = std::function<void(Args...)>;

        // Subscribe to the event
        void Subscribe(Handler handler)
        {
            handlers_.push_back(std::move(handler));
        }

        // Notify all subscribers
        void Notify(Args... args)
        {
            for (auto &h : handlers_)
            {
                h(args...);
            }
        }

    private:
        std::vector<Handler> handlers_;
    };
}

#endif //RENDIX_EVENTS_EVENT
