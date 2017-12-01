#include <ECS/ECS.hpp>
#include <ECS/StateManager.hpp>

void ECS::registerModule()
{
    StateManager::registerClass();
    GameState::registerClass();
    Entity::registerClass();
    EntityManager::registerClass();
    EventManager::registerClass();
    System::registerClass();
}
