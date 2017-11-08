#ifndef SYSTEMMANAGER_HPP
#define SYSTEMMANAGER_HPP
#include <unordered_map>
#include <Lua.hpp>
#include <System.hpp>

class SystemManager
{
public:
    static void registerClass();
    SystemManager();
    std::shared_ptr<System> addSystem(const std::string&);
    std::shared_ptr<System> getSystem(const std::string&);
    template<class T>
    void subscribe(const std::string&, T&, void (T::*)(sol::table));
    void subscribe(const std::string&, sol::object, sol::function);
    void emit(const std::string&, sol::table);
    template<class T>
    static void registerSystem(const std::string&);
private:
    std::unordered_map<std::string, std::shared_ptr<System>> m_systems;
    std::unordered_map<std::string, std::vector<std::function<void(sol::table)>>> m_eventCallbacks;
    static std::unordered_map<std::string, std::function<std::shared_ptr<System>()>> m_registeredSystems;
};

template<class T>
inline void SystemManager::subscribe(const std::string& eventName, T& obj, void (T::*functor)(sol::table))
{
    if(m_eventCallbacks.find(eventName) == std::end(m_eventCallbacks))
        m_eventCallbacks[eventName] = std::vector<std::function<void(sol::table)>>();
    auto& callbacks = m_eventCallbacks[eventName];
    callbacks.emplace_back([&obj, functor](sol::table table)
    {
        (obj.*functor)(table);
    });
}

template<class T>
inline void SystemManager::registerSystem(const std::string& systemName)
{
    static_assert(std::is_base_of<System, T>::value, " must derive from System");
    m_registeredSystems[systemName] = []() -> std::shared_ptr<T>
    {
        return std::make_shared<T>();
    };
}





#endif
