#ifndef ECS_HPP
#define ECS_HPP
#include <sol/table.hpp>
#include <memory>

class GameState;

struct ECS
{
    static sol::table createModule(sol::this_state);
    static bool init(sol::this_state);
    static void deinit();
    static void registerState(const std::string&, sol::table);
    static std::unique_ptr<GameState> createState(const std::string&);
    static void registerComponent(const std::string&, sol::table);
    static void registerEntity(const std::string&, sol::table);
    static void registerSystem(const std::string&, sol::table);
    static sol::table getSystem(const std::string&);
};

extern "C"
{
    struct lua_State;
}

extern "C" int luaopen_Zadymka_ECS(lua_State*);

#endif
