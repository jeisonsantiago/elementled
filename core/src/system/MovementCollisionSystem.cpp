#include "MovementCollisionSystem.h"

namespace elementled {

void MovementCollisionSystem::Prepare(ecs_simple::Registry *registry)
{
    // call parent class function prepare()
    System::Prepare(registry);

    // make sure p_registry is available
    assert(p_registry != nullptr && "p_registry must be a valid pointer");

    // TODO: check if they are valid
    m_transformManager = p_registry->GetComponentManager<TransformComponent>();
    m_levelManager = p_registry->GetComponentManager<LevelComponent>();
    m_kinematicBodyManager = p_registry->GetComponentManager<KinematicBodyComponent>();

    // m_colliderManager = p_registry->getComponentManager<ColliderComponent>();

    // m_tilemapManager = p_registry->getComponentManager<TileMapComponent>();

    // m_scriptManager = p_registry->getComponentManager<ScriptComponent>();
}

void MovementCollisionSystem::Update(float dt)
{
    // auto tile_component = m_tilemapManager->GetComponentByIndex(0);
    for(auto &kinematic:m_kinematicBodyManager->GetComponentVector()){
        if(kinematic.direction.x != 0 || kinematic.direction.y != 0){

        }
    }
    // if(!tile_component) return;

    // for(auto& entity:m_colliderManager->GetEntities()){
    //     auto *colliderA = m_colliderManager->GetComponentByEntity(entity);
    //     const auto *kinematicA = m_kinematicBodyManager->GetComponentByEntity(entity);
    //     auto *transformA = m_transformManager->GetComponentByEntity(entity);



    //     if(!colliderA) continue;

    //     //  if collider is not active jump to the next entity (index)
    //     if(!colliderA->is_active) continue;

    //     // now we check collision between kinematic collider and tilemap
    //     // the rule is (if has kinematic body will collide with tilemap!)
    //     if(kinematicA){

    //         // get old position
    //         math::Vec2f old_position = transformA->position;

    //         // PROCESS X axis ==========================================================
    //         // update the position with direction and speed  axis X
    //         transformA->position.x += kinematicA->direction.x * kinematicA->speed * dt;

    //         // check collision with tilemap
    //         // if(!colliderA->is_trigger){
    //         bool collidingX = tile_component->rect_colliding_tiles(
    //             transformA->position.x + colliderA->offset.x,
    //             transformA->position.y + colliderA->offset.y,
    //             colliderA->collider.width,
    //             colliderA->collider.height);

    //         // if there is a collision change transform.position to old position
    //         if(collidingX){
    //             if(!colliderA->is_trigger){
    //                 transformA->position = old_position;
    //                 colliderA->is_colliding = 4;
    //             }
    //         }

    //         // PROCESS Y axis ==========================================================
    //         // do the same with axis Y
    //         old_position = transformA->position;

    //         // update the position with direction and speed  axis Y
    //         // TODO: GO TO MOVEMENT SYSTEM (change only kinematic direction)
    //         transformA->position.y += kinematicA->direction.y * kinematicA->speed * dt;

    //         // check collision with tilemap
    //         // if(!colliderA->is_trigger){
    //         bool collidingY = tile_component->rect_colliding_tiles(
    //             transformA->position.x + colliderA->offset.x,
    //             transformA->position.y + colliderA->offset.y,
    //             colliderA->collider.width,
    //             colliderA->collider.height);

    //         // if there is a collision change transform.position to old position
    //         if(collidingY){
    //             if(!colliderA->is_trigger){
    //                 transformA->position = old_position;
    //                 colliderA->is_colliding = 8;
    //             }
    //         }
    //     }
    // }
    }
}
