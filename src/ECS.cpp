#include <include/ECS.hpp>
#include <Lua.hpp>
#include <ECS/GameState.hpp>
#include <iostream>
#include <Graphics/Window.hpp>

namespace
{
    std::unordered_map<std::string, sol::table> m_registeredStates;
    std::unordered_map<std::string, sol::table> m_registeredComponents;
    std::unordered_map<std::string, sol::table> m_registeredEntities;
    std::unordered_map<std::string, sol::table> m_registeredSystems;
}

sol::table ECS::createModule(sol::this_state L)
{
    sol::state_view lua(L);
    sol::table module = lua.create_table();
    module["init"] = &ECS::init;
    module["deinit"] = &ECS::deinit;
    module.new_usertype<GameState>("GameState", sol::constructors<GameState(), GameState(sol::table)>(),
                                   "camera", &GameState::m_camera,
                                   "eventManager", &GameState::m_eventManager,
                                   "entityManager", &GameState::m_entityManager,
                                   "addSystem", &GameState::addSystem,
                                   "getSystem", &GameState::getSystem,
                                   "removeSystem", &GameState::removeSystem,
                                   sol::meta_function::index, [](GameState& state, const std::string& key)
                                   {
                                       return state.m_table[key];
                                   },
                                   sol::meta_function::new_index, [](GameState& state, const std::string& key, sol::object value)
                                   {
                                       state.m_table[key] =  value;
                                   },
                                   "init", &GameState::init,
                                   "update", &GameState::update,
                                   "fixedUpdate", &GameState::fixedUpdate,
                                   "draw", &GameState::draw
    );
    module.new_usertype<Entity>("Entity",
                                "new", sol::no_constructor,
                                "getID", &Entity::getID,
                                "addComponent", &Entity::addComponent,
                                "get", [](Entity& e, const std::string& name) { return e.m_components[name]; },
                                "getComponents", [](Entity& e) { return e.m_components; },
                                "has", sol::overload(&Entity::hasComponent, &Entity::hasComponents),
                                "components", &Entity::m_components
    );
    module.new_usertype<EntityManager>("EntityManager",
                                       sol::constructors<EntityManager(EventManager&)>(),
                                       "createEntity", sol::overload(
                                        [](EntityManager& mgr, sol::table entityTable) -> sol::object
                                        {
                                            return mgr.createHandle(mgr.createEntity(entityTable));
                                        },
                                        [](EntityManager& mgr) -> sol::object
                                        {
                                            return mgr.createHandle(mgr.createEntity());
                                        }),
                                       "destroyEntity", &EntityManager::destroyEntity,
                                       "getEntity", [](EntityManager& mgr, std::size_t id) -> sol::object
                                       {
                                           if(mgr.m_entities.find(id) != mgr.m_entities.end())
                                               return mgr.m_handles[id];
                                           else
                                               return mgr.m_nullHandle;
                                       },
                                       "getEntities", &EntityManager::getEntities
    );
    module.new_usertype<EventManager>("EventManager",
                                      sol::constructors<EventManager()>(),
                                      "subscribe", &EventManager::subscribe,
                                      "emit", &EventManager::emit
    );
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
    
    module["registerState"] = &ECS::registerState;
    module["createState"] = &ECS::createState;
    module["registerComponent"] = &ECS::registerComponent;
    module["registerEntity"] = &ECS::registerEntity;
    module["registerSystem"] = &ECS::registerSystem;
    module["states"] = &m_registeredStates;
    module["components"] = &m_registeredComponents;
    module["entities"] = &m_registeredEntities;
    
    return module;
}

bool ECS::init(sol::this_state)
{
    return true;
}

void ECS::deinit()
{
    m_registeredStates.clear();
    m_registeredComponents.clear();
    m_registeredEntities.clear();
    m_registeredSystems.clear();
}

void ECS::registerState(const std::string &stateName, sol::table stateTable)
{
    m_registeredStates[stateName] = stateTable;
}

std::unique_ptr<GameState> ECS::createState(const std::string& stateName)
{
    if(m_registeredStates.find(stateName) != std::end(m_registeredStates))
        return std::make_unique<GameState>(m_registeredStates[stateName]);
    else
    {
        std::cerr << stateName << " has not been registered, returning nullState\n";
        return std::make_unique<GameState>();
    }
}

void ECS::registerComponent(const std::string &componentName, sol::table componentTable)
{
    m_registeredComponents[componentName] = componentTable;
}

void ECS::registerEntity(const std::string &entityName, sol::table entityTable)
{
    m_registeredEntities[entityName] = entityTable;
}

void ECS::registerSystem(const std::string &systemName, sol::table systemTable)
{
    m_registeredSystems[systemName] = systemTable;
}

sol::table ECS::getSystem(const std::string& systemName)
{
    return m_registeredSystems[systemName];
}

extern "C" int luaopen_Zadymka_ECS(lua_State* L)
{
    return sol::stack::call_lua(L, 1, ECS::createModule);
}