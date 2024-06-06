#include "Scene.h"

namespace elementled {

Scene::Scene()
{
    m_registry = std::make_shared<ecs_simple::Registry>();

    // m_textureResource = std::make_shared<ResourceAllocator<ResourceSprite>>();
}

void Scene::update(float dt){
    for(auto&sysKey:m_systemOrderedKeys){
        m_systems[sysKey]->Update(dt);
    }
}

void Scene::render(float dt){
    for(auto&sysKey:m_renderSystemOrderedKeys){
        m_renderSystems[sysKey]->Update(dt);
    }
}

}
