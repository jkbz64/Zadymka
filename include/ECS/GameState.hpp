#ifndef GAMESTATE_HPP
#define GAMESTATE_HPP
#include <Graphics/Camera.hpp>
#include <ECS/EntityManager.hpp>
#include <ECS/System.hpp>

class Window;

class GameState
{
public:
    GameState();
    GameState(sol::table);
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
    std::unordered_map<std::string, System> m_systems;
};

inline const Camera& GameState::getCamera() const
{
    return m_camera;
}

#endif
