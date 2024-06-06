#ifndef MOVEMENTCOLLISIONSYSTEM_H
#define MOVEMENTCOLLISIONSYSTEM_H

#include "ecs/ECSSimple.h"
#include "system/System.h"
#include "components/Components.h"

namespace elementled{

class MovementCollisionSystem:public System
{
public:
    MovementCollisionSystem() = default;

    void Prepare(ecs_simple::Registry *registry) override;

    void Update(float dt) override;

private:
    std::shared_ptr<ecs_simple::ComponentManager<TransformComponent>> m_transformManager;
    // std::shared_ptr<ecs_simple::ComponentManager<ColliderComponent>> m_colliderManager;
    std::shared_ptr<ecs_simple::ComponentManager<LevelComponent>> m_levelManager;
    // std::shared_ptr<ecs_simple::ComponentManager<LevelComponent>> m_levelManager;
    std::shared_ptr<ecs_simple::ComponentManager<KinematicBodyComponent>> m_kinematicBodyManager;
};

}
#endif // MOVEMENTCOLLISIONSYSTEM_H
