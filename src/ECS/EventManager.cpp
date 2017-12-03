#include <ECS/EventManager.hpp>

void EventManager::registerClass(sol::table module)
{
    module.new_usertype<EventManager>("EventManager",
                                               sol::constructors<EventManager()>(),
                                               "subscribe", &EventManager::subscribe,
                                               "emit", &EventManager::emit
                                               );
}

void EventManager::subscribe(const std::string& eventName, sol::object obj, sol::function f)
{
    if(m_eventCallbacks.find(eventName) == std::end(m_eventCallbacks))
        m_eventCallbacks[eventName] = std::vector<std::function<void(sol::table)>>();
    std::vector<std::function<void(sol::table)>>& callbacks = m_eventCallbacks[eventName];
    callbacks.emplace_back([obj, f](sol::table table)
    {
        if(obj.valid())
            f.call(obj, table)  ;
    });
}

void EventManager::emit(const std::string& eventName, sol::table table)
{
    if(m_eventCallbacks.find(eventName) != std::end(m_eventCallbacks))
    {
        const auto& callbacks = m_eventCallbacks[eventName];
        std::for_each(std::begin(callbacks), std::end(callbacks), [&table](std::function<void(sol::table)> f)
        {
            f(table);
        });
    }
}
