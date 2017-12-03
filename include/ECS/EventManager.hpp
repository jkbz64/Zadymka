#ifndef EVENTMANAGER_HPP
#define EVENTMANAGER_HPP
#include <unordered_map>
#include <sol/table.hpp>

class EventManager
{
public:
    static void registerClass(sol::table);
    EventManager() = default;
    EventManager(const EventManager&) = delete;
    EventManager(EventManager&&) = delete;
    EventManager& operator=(const EventManager&) = delete;
    EventManager& operator=(EventManager&&) = delete;
    ~EventManager() = default;
    void subscribe(const std::string&, sol::object, sol::function);
    void emit(const std::string&, sol::table);
private:
     std::unordered_map<std::string, std::vector<std::function<void(sol::table)>>> m_eventCallbacks;
};

#endif