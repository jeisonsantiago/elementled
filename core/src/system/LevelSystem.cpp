#include "LevelSystem.h"

namespace elementled{
LevelSystem::LevelSystem() {}

void LevelSystem::Prepare(ecs_simple::Registry *registry)
{
    System::Prepare(registry);

    // get necessary component managers
    m_infoManager = p_registry->GetComponentManager<InfoComponent>();
    m_levelManager = p_registry->GetComponentManager<LevelComponent>();
    m_transformsManager = p_registry->GetComponentManager<TransformComponent>();
    m_shapesManager = p_registry->GetComponentManager<PrimitiveShapeComponent>();


}

void LevelSystem::Update(float dt)
{
// get the level
// check if it's active
// create entitites

    if(!loaded){
        this->LoadLevel();
        loaded = true;
    }

}

void LevelSystem::LoadLevel()
{
    for(ecs_simple::Entity e:m_levelManager->GetEntities()){
        auto *level = m_levelManager->GetComponentByEntity(e);
        if(level->isCurrent){
            // get transform
            const auto *transform = m_transformsManager->GetComponentByEntity(e);

            // TraceLog(LOG_INFO,"%d %d",(int)transform->position.x,(int)transform->position.y);
            int parentTransformX = (int)transform->position.x;
            int parentTransformY = (int)transform->position.y;

            for (int r = 0; r < level->matrix.rows; ++r) {
                for (int c = 0; c < level->matrix.cols; ++c) {

                    if(level->matrix(r,c) == 0) continue;

                    // create entity
                    ecs_simple::Entity tileEntity = p_registry->CreateEntity();

                    int newPosX = (c * level->tileWidth)  + parentTransformX;
                    int newPosY = (r * level->tileHeight) + parentTransformY;
                    // create primitive component
                    m_transformsManager->Create(
                        tileEntity,
                        newPosX,newPosY
                        );

                    // TraceLog(LOG_INFO,"%d %d",newPosX,newPosY);


                    m_shapesManager->Create(tileEntity,level->tileWidth,level->tileHeight,BROWN,RECTANGLE_LINE);
                }
            }
        }
    }
}

}


