#include <ECS/EntityManager.hpp>
#include <Lua.hpp>

EntityManager::EntityManager(EventManager& manager) :
    m_eventManager(manager),
    m_nullEntity(nullptr, -1)
{
    m_magicMetatable = Lua::getState().script(R"(
    memoizedFuncs = {}
    local mt = {}
    mt.__index = function(handle, key)
        if not handle.isValid then
            print(debug.traceback())
            error("Error: handle is not valid!", 2)
        end

        local f = memoizedFuncs[key]
        if not f then
            f = function(handle, ...) return Entity[key](handle.cppRef, ...) end
            memoizedFuncs[key] = f
        end
        return f
    end
    return mt
    )");
    m_handles = Lua::getState().create_table();
    m_nullHandle = createHandle(m_nullEntity);
}

EntityManager::~EntityManager()
{
    Lua::scriptArgs(
    R"(
    for _, v in pairs(arg[1]) do
        v.isValid = false
    end
    )", m_handles);
}

Entity& EntityManager::createEntity()
{
    const auto id = m_poolIndex++;
    auto inserted = m_entities.emplace(std::piecewise_construct,
                                       std::forward_as_tuple(id),
                                       std::forward_as_tuple(this, id));
    auto it = inserted.first;
    auto& e = it->second;
    m_eventManager.emit("EntityCreated", Lua::getState().create_table_with("entity", &e));
    return e;
}

Entity& EntityManager::createEntity(sol::table componentTable)
{
    const auto id = m_poolIndex++;
    auto inserted = m_entities.emplace(std::piecewise_construct,
                                       std::forward_as_tuple(id),
                                       std::forward_as_tuple(this, id));
    auto it = inserted.first;
    auto& e = it->second;

    for(std::pair<sol::object, sol::table> pair : componentTable)
    {
        std::string componentName = pair.first.as<std::string>();
        e.addComponent(componentName, pair.second);
    }

    m_eventManager.emit("EntityCreated", Lua::getState().create_table_with("entity", createHandle(e)));
    return e;
}

void EntityManager::destroyEntity(std::size_t id)
{
    auto& entity = m_entities.at(id);
    m_eventManager.emit("EntityDestroyed", Lua::getState().create_table_with("entity", createHandle(entity)));
    m_entities.erase(id);
}

Entity& EntityManager::getEntity(std::size_t id)
{
    if(m_entities.find(id) != m_entities.end())
        return m_entities.find(id)->second;
    else
        return m_nullEntity;
}

sol::object EntityManager::createHandle(Entity& e)
{
    return Lua::scriptArgs(
    R"(
    function getWrappedSafeFunction(f)
        return function(handle, ...)
            if not handle.isValid then
                print(debug.traceback())
                    error("Error: handle is not valid!", 2)
                end
             return f(handle.cppRef, ...)
        end
    end

    local handle = {
        cppRef = arg[3],
        isValid = true
    }

    -- speedy access without __index call
    handle.getID = getWrappedSafeFunction(Entity.getID)

    setmetatable(handle, arg[1])
    arg[2][arg[3]:getID()] = handle
    return handle
    )", m_magicMetatable, m_handles, e);
}

std::vector<std::reference_wrapper<Entity>> EntityManager::getEntities()
{
    std::vector<std::reference_wrapper<Entity>> entities;
    entities.reserve(m_entities.size());
    for(auto& entity : m_entities)
        entities.emplace_back(entity.second);
    return entities;
}

sol::table EntityManager::getDefaultComponent(const std::string& componentName)
{
    return Lua::getState()["ECS"]["components"][componentName];
}
