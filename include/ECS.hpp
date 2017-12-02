#ifndef ECS_HPP
#define ECS_HPP
#include <Lua.hpp>

namespace ECS
{
    void registerModule();
    bool init();
    void deinit();
    void registerState(const std::string&, sol::table);
    void registerComponent(const std::string&, sol::table);
    void registerEntity(const std::string&, sol::table);
}

#endif
