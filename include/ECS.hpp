#ifndef ECS_HPP
#define ECS_HPP
#include <sol/table.hpp>

namespace ECS
{
    sol::table createModule(sol::this_state);
    bool init();
    void deinit();
    void registerState(const std::string&, sol::table);
    void registerComponent(const std::string&, sol::table);
    void registerEntity(const std::string&, sol::table);
    void registerSystem(const std::string&, sol::table);
    sol::table getSystem(const std::string&);
}

extern "C"
{
    struct lua_State;
}

extern "C" int luaopen_Zadymka_ECS(lua_State*);

#endif
