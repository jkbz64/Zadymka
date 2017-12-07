#include <ECS/System.hpp>
#include <Lua.hpp>

System::System()
{

}

System::System(sol::table systemTable)
{
    m_systemTable = Lua::getState().create_table();
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