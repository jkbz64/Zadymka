#ifndef ECS_HPP
#define ECS_HPP
#include <sol/forward.hpp>
#include <memory>

class GameState;

struct ECS
{
    static sol::table createModule(sol::this_state);
    static bool init(sol::this_state);
    static void deinit();
    static void registerState(const std::string&, sol::table);
    static std::unique_ptr<GameState> createState(sol::this_state, const std::string&);
};

extern "C"
{
    struct lua_State;
}

extern "C" int luaopen_Zadymka_ECS(lua_State*);

#endif
