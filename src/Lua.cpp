#include <Lua.hpp>

namespace
{
    lua_State* lua(nullptr);
}

void Lua::setState(lua_State *L)
{
    lua = L;
}

sol::state_view Lua::getState()
{
    if(lua == nullptr)
        throw std::logic_error("Zadymka hasn't been initialized. Please call init function");
    else
        return sol::state_view(lua);
}

