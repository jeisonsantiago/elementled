#ifndef LEVELRENDERSYSTEM_H
#define LEVELRENDERSYSTEM_H

#include "ecs/ECSSimple.h"
#include "components/Components.h"
#include "system/System.h"

namespace elementled{

class LevelRenderSystem: public System
{
public:
    LevelRenderSystem();
    void Prepare(ecs_simple::Registry *registry) override;
    void Update(float dt) override;
    // void LoadLevel();

private:
    std::shared_ptr<ecs_simple::ComponentManager<InfoComponent>> m_infoManager;
    std::shared_ptr<ecs_simple::ComponentManager<LevelComponent>> m_levelManager;
    std::shared_ptr<ecs_simple::ComponentManager<TransformComponent>> m_transformsManager;
    std::shared_ptr<ecs_simple::ComponentManager<PrimitiveShapeComponent>> m_shapesManager;

    bool loaded = false;
};

}

#endif // LEVELRENDERSYSTEM_H
