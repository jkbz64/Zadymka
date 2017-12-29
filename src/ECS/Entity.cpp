#include <ECS/Entity.hpp>
#include <sol/state_view.hpp>

#include <ECS/EntityManager.hpp>
#include <iostream>

Entity::Entity(EntityManager* manager, EventManager* eventManager, unsigned int id) :
    m_manager(manager),
    m_eventManager(eventManager),
    m_id(id)
{

}

void Entity::addComponent(const std::string& componentName, sol::table table)
{
    auto defaultComponent = m_manager->getDefaultComponent(componentName);
    if(defaultComponent.valid())
    {
        sol::state_view lua(table.lua_state());
        sol::table componentTable = m_components[componentName] = lua.create_table();
        //First copy from given table
        for(std::pair<sol::object, sol::object> cVar : table)
        {
            std::string key = cVar.first.as<std::string>();
            sol::object value = cVar.second;
            sol::type type = value.get_type();
            
            if(type == sol::type::number  || // Copy POD
               type == sol::type::boolean ||
               type == sol::type::string  ||
               type == sol::type::function)
            {
                componentTable[key] = value;
            }
            else if(type == sol::type::userdata) // Copy Userdata's by using copy constructor
            {
                sol::userdata ud = value;
                sol::table metatable = ud[sol::metatable_key];
                sol::object copied = metatable["new"].call(value);
                componentTable[key] = copied;
            }
            else if(type == sol::type::table) // TODO table copy
            {
                //TODO
            }
            else // Fallback to POD copy, welp
            {
                componentTable[key] = value;
            }
        }
        //Now copy remaining field if they are not present
        for(std::pair<sol::object, sol::object> cVar : defaultComponent)
        {
            std::string key = cVar.first.as<std::string>();
            sol::object value = cVar.second;
            sol::type type = value.get_type();
            
            if(componentTable[key].valid()) // Skip copying existing variables
                continue;
        
            if(type == sol::type::number  || // Copy POD
               type == sol::type::boolean ||
               type == sol::type::string  ||
               type == sol::type::function)
            {
                componentTable[key] = value;
            }
            else if(type == sol::type::userdata) // Copy Userdata's by using copy constructor
            {
                sol::userdata ud = value;
                sol::table metatable = ud[sol::metatable_key];
                sol::object copied = metatable["new"].call(value);
                componentTable[key] = copied;
            }
            else if(type == sol::type::table) // TODO table copy
            {
                //TODO
            }
            else // Fallback to POD copy, welp
            {
                componentTable[key] = value;
            }
        }
    }
    else
        std::cerr << componentName << " couldn't be found. Register component before adding to entity\n";
}

bool Entity::hasComponent(const std::string& name)
{
    return m_components.find(name) != std::end(m_components);
}

bool Entity::hasComponents(const std::vector<std::string>& names)
{
    bool has = true;
    if(!names.empty())
    {
        for(const auto& name : names)
            has = has && hasComponent(name);
    }
    return has;
}

sol::table Entity::getComponent(const std::string &componentName)
{
    if(m_components.find(componentName) != m_components.end())
        return m_components[componentName];
    return sol::table{};
}
