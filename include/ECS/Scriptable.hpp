#ifndef SCRIPTABLE_HPP
#define SCRIPTABLE_HPP
#include <sol/state_view.hpp>

class BaseScriptable
{
public:
    BaseScriptable() = default;
    virtual ~BaseScriptable() = default;
protected:
    friend class ECS;
    sol::table m_table;
};

template<class T>
class Scriptable : public BaseScriptable
{
public:
    Scriptable() :
            m_lua(nullptr)
    {
    
    }
    Scriptable(sol::this_state L) :
            m_lua(L)
    {
        m_table = m_lua.create_table();
    }
    Scriptable(sol::this_state L, sol::table table) :
            m_lua(L)
    {
        m_table = m_lua.create_table();
        for(std::pair<sol::object, sol::object> p : table)
        {
            std::string key = p.first.as<std::string>();
            auto val = p.second;
            if(val.get_type() == sol::type::function)
            {
                sol::function f = val.as<sol::function>();
                m_table[key] = [&, f](T& system, sol::variadic_args args)
                {
                    sol::object oldSelf;
                    if(m_lua["self"].valid())
                        oldSelf = m_lua["self"];
                    m_lua.set("self", &system);
                    f.call(args);
                    if(oldSelf.valid())
                        m_lua.set("self", oldSelf);
                    else
                        m_lua.set("self", sol::nil);
                };
            }
            else
                m_table[key] = val;
        }
    }
    virtual ~Scriptable() = default;
protected:
    sol::state_view m_lua;
};

#endif