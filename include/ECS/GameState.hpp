#ifndef GAMESTATE_HPP
#define GAMESTATE_HPP
#include <Graphics/Camera.hpp>
#include <ECS/EntityManager.hpp>
#include <ECS/System.hpp>

class Window;

class GameState
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

    void init() const;
    void cleanup() const;
    void update(double dt) const;
    void fixedUpdate(double dt) const;
    void draw(Window& window, double alpha) const;

    const Camera& getCamera() const;
    
    System& addSystem(const std::string&);
    void removeSystem(const std::string&);
    System& getSystem(const std::string&);
protected:
    sol::state_view m_lua;
    friend class ECS;
    sol::table m_table;
    std::function<void()> m_init;
    std::function<void()> m_cleanup;
    std::function<void(double)> m_update;
    std::function<void(double)> m_fixedUpdate;
    std::function<void(Window&, double)> m_draw;
    //Camera
    Camera m_camera;
    //ECS
    EventManager m_eventManager;
    EntityManager m_entityManager;
    System m_nullSystem;
    std::unordered_map<std::string, System> m_systems;
    static std::unordered_map<std::string, sol::table> m_registeredSystems;
};

#endif
