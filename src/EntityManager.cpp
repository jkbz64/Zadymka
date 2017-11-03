#include <EntityManager.hpp>
#include <Lua.hpp>

void EntityManager::registerClass()
{
    Lua::getState().new_usertype<EntityManager>("EntityManager",
                                                sol::constructors<EntityManager()>(),
                                                "createEntity", [](EntityManager& mgr)
                                                {
                                                    return mgr.createHandle(mgr.createEntity());
                                                }
    );
}

EntityManager::EntityManager()
{
    m_magicMetatable = Lua::getState().script(R"(
    function getWrappedSafeFunction(f)
        return function(handle, ...)
            if not handle.isValid then
                print(debug.traceback())
                    error("Error: handle is not valid!", 2)
                end
             return f(handle.cppRef, ...)
        end
    end

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
}

Entity& EntityManager::createEntity()
{
    const auto id = m_poolIndex++;
    auto inserted = m_entities.emplace(id, id);
    auto it = inserted.first;
    auto& e = it->second;
    return e;
}

sol::object EntityManager::createHandle(Entity& e)
{
    static sol::function createHandleFnc = Lua::getState().script(
    R"(
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
