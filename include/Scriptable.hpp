#ifndef SCRIPTABLE_HPP
#define SCRIPTABLE_HPP
#include <sol/state.hpp>

struct Lua
{
    static sol::state& getState()
    {
        static sol::state state = sol::state();
        return state;
    }
};

template<class T>
class Scriptable
{
public:
    Scriptable()
    {
        static bool exposed = false;
        if(!exposed)
        {
            T::exposeToLua();
            exposed = true;
        }
    }
    virtual ~Scriptable() = default;
};

#endif
