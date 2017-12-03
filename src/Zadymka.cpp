#include <Zadymka.hpp>
#include <sol/state_view.hpp>
#include <Math.hpp>
#include <Graphics.hpp>
#include <Audio.hpp>
#include <ECS.hpp>

sol::table Zadymka::createModule(sol::this_state L)
{
    sol::state_view lua(L);
    sol::table module = lua.create_table();
    module["init"] = &Zadymka::init;
    module["deinit"] = &Zadymka::deinit;
    module["Math"] = Math::createModule(L);
    module["Graphics"] = Graphics::createModule(L);
    module["ECS"] = ECS::createModule(L);
    //module["Audio"] = Audio::createModule(L);
    return module;
}

void Zadymka::init(sol::this_state L)
{
    //Set state to lua singleton
    Lua::setState(L);
    
    Graphics::init();
    //Audio::init();
    ECS::init();
}

void Zadymka::deinit(sol::this_state)
{
    Graphics::deinit();
    //Audio::deinit();
    ECS::deinit();
    Lua::setState(nullptr);
}

extern "C" int luaopen_Zadymka(lua_State* L)
{
    return sol::stack::call_lua(L, 1, Zadymka::createModule);
}