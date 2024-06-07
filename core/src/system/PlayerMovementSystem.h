#ifndef PLAYERMOVEMENTSYSTEM_H
#define PLAYERMOVEMENTSYSTEM_H

#include "ecs/ECSSimple.h"
#include "system/System.h"
#include "components/Components.h"


namespace elementled{


class PlayerMovementSystem: public System
{
public:
    PlayerMovementSystem();
    void Prepare(ecs_simple::Registry *registry) override;
    void Update(float dt) override;
private:
    std::shared_ptr<ecs_simple::ComponentManager<InfoComponent>> m_infoManager;
    std::shared_ptr<ecs_simple::ComponentManager<KinematicBodyComponent>> m_kinematicBodyManager;
};

}

#endif // PLAYERMOVEMENTSYSTEM_H
