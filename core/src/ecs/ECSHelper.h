#ifndef ECSHELPER_H
#define ECSHELPER_H

#include "ECSSimple.h"
#include "components/Components.h"

namespace elementled{

struct GameObject{
    ecs_simple::Entity entity = ecs_simple::INVALID_ENTITY;
    TransformComponent* transformComponent = nullptr;
    RelationshipComponent* relationshipComponent = nullptr;
    InfoComponent* infoComponent = nullptr;
};

static GameObject CreateGameObject(
    std::shared_ptr<ecs_simple::Registry> registry,
    float x, float y
    )
    {

    ecs_simple::Entity entity = registry->CreateEntity();

    GameObject gameObject;
    gameObject.entity = entity;

    gameObject.transformComponent =     &registry->CreateComponent<TransformComponent>(entity,x,y);
    gameObject.relationshipComponent =  &registry->CreateComponent<RelationshipComponent>(entity);
    gameObject.infoComponent =          &registry->CreateComponent<InfoComponent>(entity);

    return gameObject;
}
}



#endif // ECSHELPER_H
