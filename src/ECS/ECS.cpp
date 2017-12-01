#include <ECS/ECS.hpp>
#include <ECS/Entity.hpp>
#include <ECS/EntityManager.hpp>
#include <ECS/System.hpp>
#include <ECS/SystemManager.hpp>

void ECS::registerModule()
{
    Entity::registerClass();
    EntityManager::registerClass();
    EventManager::registerClass();
    System::registerClass();
    SystemManager::registerClass();
}
