#ifndef LEVELSYSTEM_H
#define LEVELSYSTEM_H

#include "ecs/ECSSimple.h"
#include "components/Components.h"
#include "system/System.h"

namespace elementled{

class LevelSystem: public System
{
public:
    LevelSystem();
    void Prepare(ecs_simple::Registry *registry) override;
    void Update(float dt) override;
    void LoadLevel();

private:
    std::shared_ptr<ecs_simple::ComponentManager<InfoComponent>> m_infoManager;
    std::shared_ptr<ecs_simple::ComponentManager<LevelComponent>> m_levelManager;
    std::shared_ptr<ecs_simple::ComponentManager<TransformComponent>> m_transformsManager;
    std::shared_ptr<ecs_simple::ComponentManager<PrimitiveShapeComponent>> m_shapesManager;

    bool loaded = false;
};

}

#endif // LEVELSYSTEM_H
