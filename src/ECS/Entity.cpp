#include <ECS/Entity.hpp>
#include <sol/state_view.hpp>
#include <sol/table.hpp>
#include <Lua.hpp>
#include <ECS/EntityManager.hpp>
#include <iostream>

void Entity::registerClass(sol::table module)
{
    module.new_usertype<Entity>("Entity",
                                         "new", sol::no_constructor,
                                         "getID", &Entity::getID,
                                         "addComponent", &Entity::addComponent,
                                         "get", [](Entity& e, const std::string& name) { return e.m_components[name]; },
                                         "getComponents", [](Entity& e) { return e.m_components; },
                                         "has", sol::overload(&Entity::hasComponent, &Entity::hasComponents),
                                         "components", &Entity::m_components
    );
}

Entity::Entity(EntityManager* manager, int id) :
    m_manager(manager),
    m_id(id)
{

}

int Entity::getID()
{
    return m_id;
}

void Entity::addComponent(const std::string& componentName, sol::table table)
{
    auto defaultComponent = m_manager->getDefaultComponent(componentName);
    if(defaultComponent.valid())
    {
        sol::table componentTable = m_components[componentName] = Lua::getState().create_table();
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
                sol::object copied = Lua::scriptArgs("return getmetatable(arg[1]).new(arg[1])", value);
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
                sol::object copied = Lua::scriptArgs("return getmetatable(arg[1]).new(arg[1])", value);
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
