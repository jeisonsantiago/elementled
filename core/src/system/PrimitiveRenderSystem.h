#ifndef PRIMITIVERENDERSYSTEM_H
#define PRIMITIVERENDERSYSTEM_H

#include "ecs/ECSSimple.h"
#include "components/Components.h"
#include "system/System.h"

namespace elementled {

class PrimitiveRenderSystem: public System
{
public:
    PrimitiveRenderSystem();
    void Prepare(ecs_simple::Registry *registry) override;
    void Update(float dt) override;
private:
    std::shared_ptr<ecs_simple::ComponentManager<TransformComponent>> m_transformsManager;
    std::shared_ptr<ecs_simple::ComponentManager<PrimitiveShapeComponent>> m_shapesManager;
};


}

#endif // PRIMITIVERENDERSYSTEM_H
