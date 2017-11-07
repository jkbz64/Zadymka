#include <EntityManager.hpp>
#include <Lua.hpp>

void EntityManager::registerClass()
{
    Lua::getState().new_usertype<EntityManager>("EntityManager",
                                                sol::constructors<EntityManager(SystemManager&)>(),
                                                "createEntity", [](EntityManager& mgr)
                                                {
                                                    return mgr.createHandle(mgr.createEntity());
                                                },
                                                "getEntity", [](EntityManager& mgr, std::size_t id) -> sol::object
                                                {
                                                    if(mgr.m_entities.find(id) != mgr.m_entities.end())
                                                        return mgr.m_handles[id];
                                                    else
                                                        return mgr.m_nullHandle;
                                                },
                                                "getEntities", &EntityManager::getEntities
    );
}

EntityManager::EntityManager(SystemManager& manager) :
    m_systemManager(manager),
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
    m_handles = Lua::getState().script("return {}");
    m_nullHandle = createHandle(m_nullEntity);
}

Entity& EntityManager::createEntity()
{
    const auto id = m_poolIndex++;
    auto inserted = m_entities.emplace(std::piecewise_construct,
                                       std::forward_as_tuple(id),
                                       std::forward_as_tuple(this, id));
    auto it = inserted.first;
    auto& e = it->second;
    m_systemManager.emit("EntityCreated", Lua::getState().create_table_with("entity", &e));
    return e;
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
    static sol::function createHandleFnc = Lua::getState().script(
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

    local createHandle = function(mt, Handles, cppRef)
        local handle = {
            cppRef = cppRef,
            isValid = true
        }

        -- speedy access without __index call
        handle.getID = getWrappedSafeFunction(Entity.getID)

        setmetatable(handle, mt)
        Handles[cppRef:getID()] = handle
        return handle
    end
    return createHandle
    )");
    return createHandleFnc.call(m_magicMetatable, m_handles, e);
}

std::vector<std::reference_wrapper<Entity>> EntityManager::getEntities()
{
    std::vector<std::reference_wrapper<Entity>> entities;
    entities.reserve(m_entities.size());
    for(auto& entity : m_entities)
        entities.emplace_back(entity.second);
    return entities;
}

sol::object EntityManager::createComponent(Entity& entity, const std::string& componentName, sol::variadic_args args)
{
    static sol::function initializeFunc = Lua::getState().script(R"(
    local createComponent = function(componentName, ...)
        local componentClass = dofile('components/' .. componentName .. '.lua')
        return componentClass(...)
    end
    return createComponent
    )");
    //TODO - Add entity to systems
    return initializeFunc.call(componentName, args);
}
