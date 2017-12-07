#include <ECS.hpp>
#include <ECS/GameState.hpp>
#include <iostream>
#include <Graphics/Window.hpp>

namespace
{
    std::unordered_map<std::string, sol::table> m_registeredStates;
}

sol::table ECS::createModule(sol::this_state L)
{
    sol::state_view lua(L);
    sol::table module = lua.create_table();
    module["init"] = &ECS::init;
    module["deinit"] = &ECS::deinit;
    module.new_usertype<GameState>("GameState", sol::constructors<GameState(sol::this_state), GameState(sol::this_state, sol::table)>(),
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
                                "id", sol::readonly(&Entity::m_id),
                                "addComponent", &Entity::addComponent,
                                "get", [](Entity& e, const std::string& name) { return e.m_components[name]; },
                                "getComponents", [](Entity& e) { return e.m_components; },
                                "has", sol::overload(&Entity::hasComponent, &Entity::hasComponents),
                                "components", &Entity::m_components
    );
    module.new_usertype<EntityManager>("EntityManager", "new", sol::no_constructor,
                                       "createEntity", sol::overload(
                                            [](EntityManager& mgr) -> Entity&
                                            {
                                                return mgr.createEntity();
                                            },
                                            static_cast<Entity&(EntityManager::*)(const std::string&)>(&EntityManager::createEntity),
                                            static_cast<Entity&(EntityManager::*)(sol::table)>(&EntityManager::createEntity)
                                        ),
                                       "destroyEntity", &EntityManager::destroyEntity,
                                       "getEntity", &EntityManager::getEntity
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
    module["registerComponent"] = &EntityManager::registerComponent;
    module["registerEntity"] = &EntityManager::registerEntity;
    module["registerSystem"] = &GameState::registerSystem;
    module["states"] = &m_registeredStates;
    module["components"] = &EntityManager::m_registeredComponents;
    module["entities"] = &EntityManager::m_registeredEntities;
    
    return module;
}

bool ECS::init(sol::this_state)
{
    return true;
}

void ECS::deinit()
{
    m_registeredStates.clear();
    GameState::m_registeredSystems.clear();
    EntityManager::m_registeredEntities.clear();
    EntityManager::m_registeredComponents.clear();
}

void ECS::registerState(const std::string &stateName, sol::table stateTable)
{
    m_registeredStates[stateName] = stateTable;
}

std::unique_ptr<GameState> ECS::createState(sol::this_state L, const std::string& stateName)
{
    if(m_registeredStates.find(stateName) != std::end(m_registeredStates))
        return std::make_unique<GameState>(L, m_registeredStates[stateName]);
    else
    {
        std::cerr << stateName << " has not been registered, returning nullState\n";
        return std::make_unique<GameState>(L);
    }
}

extern "C" int luaopen_Zadymka_ECS(lua_State* L)
{
    return sol::stack::call_lua(L, 1, ECS::createModule);
}