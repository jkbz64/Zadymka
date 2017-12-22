#include <Zadymka.hpp>
#include <Math.hpp>
#include <Graphics.hpp>
#include <Audio.hpp>
#include <ECS.hpp>
#include <Timer.hpp>
#include <Input.hpp>
#include <sol/state_view.hpp>
#include <ImGui.hpp>

sol::table Zadymka::createModule(sol::this_state L)
{
    sol::state_view lua(L);
    sol::table module = lua.create_table();
    module["init"] = &Zadymka::init;
    module["deinit"] = &Zadymka::deinit;
    module["Math"] = Math::createModule(L);
    module["Graphics"] = Graphics::createModule(L);
    module["ECS"] = ECS::createModule(L);
    module["Timer"] = Timer::createModule(L);
    module["Input"] = Input::createModule(L);
    module["ImGui"] = ImGUI::createModule(L);
    //module["Audio"] = Audio::createModule(L);
    return module;
}

bool Zadymka::init(sol::this_state L)
{
    return Graphics::init(L); /* && Audio::init() && */
}

void Zadymka::deinit(sol::this_state)
{
    Graphics::deinit();
    //Audio::deinit();
    ECS::deinit();
}

extern "C" int luaopen_Zadymka(lua_State* L)
{
    return sol::stack::call_lua(L, 1, Zadymka::createModule);
}