#include "PlayerMovementSystem.h"
namespace elementled{
PlayerMovementSystem::PlayerMovementSystem() {}

void PlayerMovementSystem::Prepare(ecs_simple::Registry *registry)
{
    // call parent class function prepare()
    System::Prepare(registry);

    // make sure p_registry is available
    assert(p_registry != nullptr && "p_registry must be a valid pointer");

    // TODO: check if they are valid
    m_infoManager = p_registry->GetComponentManager<InfoComponent>();
    m_kinematicBodyManager = p_registry->GetComponentManager<KinematicBodyComponent>();
}

void PlayerMovementSystem::Update(float dt)
{
    for(auto e:m_infoManager->GetEntities()){
        auto *info = m_infoManager->GetComponentByEntityNoCheck(e);
        if(info->tag.compare("player")){
            auto *kinematic = m_kinematicBodyManager->GetComponentByEntityNoCheck(e);

            if(!kinematic) continue;

            math::Vec2<float>motion = {0.0f,0.0f};

            // analise keys
            if(IsKeyDown(KEY_A)){
                motion.x = -1.0f;
                // motion.y = 0.0f;
            }else if(IsKeyDown(KEY_D)){
                motion.x = 1.0f;
                // motion.y = 0.0f;
            }

            if(IsKeyDown(KEY_W)){
                motion.y = -1.0f;
                // motion.x = 0.0f;
            }else if(IsKeyDown(KEY_S)){
                motion.y = 1.0f;
                // motion.x = 0.0f;
            }

            kinematic->direction = motion.normalize();
        }
    }
}
}


