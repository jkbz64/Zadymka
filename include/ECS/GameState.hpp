#ifndef GAMESTATE_HPP
#define GAMESTATE_HPP
#include <Graphics/Camera.hpp>
#include <ECS/EntityManager.hpp>
#include <ECS/System.hpp>

class Window;

class GameState : public Scriptable<GameState>
{
public:
    static void registerSystem(const std::string&, sol::table);
    GameState(sol::this_state);
    GameState(sol::this_state, sol::table);
    GameState(const GameState&) = delete;
    GameState& operator=(const GameState&) = delete;
    GameState(GameState&&) = delete;
    GameState& operator=(GameState&&) = delete;
    ~GameState();
    
    System& addSystem(const std::string&);
    void removeSystem(const std::string&);
    System& getSystem(const std::string&);
protected:
    friend class ECS;
    EventManager m_eventManager;
    EntityManager m_entityManager;
    System m_nullSystem;
    std::unordered_map<std::string, System> m_systems;
    static std::unordered_map<std::string, sol::table> m_registeredSystems;
};

#endif
