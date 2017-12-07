#include <ECS/System.hpp>

System::System() :
    m_lua(nullptr)
{

}

System::System(sol::this_state L) :
    m_lua(L)
{

}

System::System(sol::this_state L, sol::table systemTable) :
    System(L)
{
    m_systemTable = m_lua.create_table();
    for(std::pair<sol::object, sol::object> p : systemTable)
    {
        std::string key = p.first.as<std::string>();
        auto val = p.second;
        if(val.get_type() == sol::type::function)
        {
            sol::function f = val.as<sol::function>();
            m_systemTable[key] = [f](System& system, sol::variadic_args args)
            {
                f.call(&system, args);
            };
        }
        else
            m_systemTable[key] = val;
    }
    init = m_systemTable["init"];
}