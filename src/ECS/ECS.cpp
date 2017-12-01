#include <ECS/ECS.hpp>
#include <ECS/StateManager.hpp>
#include <ECS/GameState.hpp>
#include <ECS/Entity.hpp>
#include <ECS/EntityManager.hpp>
#include <ECS/System.hpp>

void ECS::registerModule()
{
    StateManager::registerClass();
    GameState::registerClass();
    Entity::registerClass();
    EntityManager::registerClass();
    EventManager::registerClass();
    System::registerClass();
}
