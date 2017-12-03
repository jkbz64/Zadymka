#include <ECS/System.hpp>
#include <ECS/EventManager.hpp>
#include <ECS/EntityManager.hpp>
#include <Graphics/Window.hpp>
#include <iostream>
#include <Lua.hpp>

void System::registerClass(sol::table module)
{
    module.new_usertype<System>("System", "new", sol::no_constructor,
                                         sol::meta_function::index, [](System& system, const std::string& name)
                                         {
                                             return system.m_systemTable[name];
                                         },
                                         sol::meta_function::new_index, [](System& system, const std::string& key, sol::object value)
                                         {
                                             system.m_systemTable[key] = value;
                                         }
    );
}

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