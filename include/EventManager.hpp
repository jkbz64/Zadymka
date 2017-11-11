#ifndef EVENTMANAGER_HPP
#define EVENTMANAGER_HPP
#include <unordered_map>
#include <Lua.hpp>

class EventManager
{
public:
    static void registerClass();
    EventManager();
    template<class T>
    void subscribe(const std::string&, T&, void (T::*)(sol::table));
    void subscribe(const std::string&, sol::object, sol::function);
    void emit(const std::string&, sol::table);
private:
     std::unordered_map<std::string, std::vector<std::function<void(sol::table)>>> m_eventCallbacks;
};

template<class T>
inline void EventManager::subscribe(const std::string& eventName, T& obj, void (T::*functor)(sol::table))
{
    if(m_eventCallbacks.find(eventName) == std::end(m_eventCallbacks))
        m_eventCallbacks[eventName] = std::vector<std::function<void(sol::table)>>();
    auto& callbacks = m_eventCallbacks[eventName];
    callbacks.emplace_back([&obj, functor](sol::table table)
    {
        (obj.*functor)(table);
    });
}

#endif
