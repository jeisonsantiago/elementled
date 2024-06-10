#include "LevelRenderSystem.h"

namespace elementled{
LevelRenderSystem::LevelRenderSystem() {}

void LevelRenderSystem::Prepare(ecs_simple::Registry *registry)
{
    System::Prepare(registry);

    // get necessary component managers
    m_infoManager = p_registry->GetComponentManager<InfoComponent>();
    m_levelManager = p_registry->GetComponentManager<LevelComponent>();
    m_transformsManager = p_registry->GetComponentManager<TransformComponent>();
    m_shapesManager = p_registry->GetComponentManager<PrimitiveShapeComponent>();


}

void LevelRenderSystem::Update(float dt)
{
    for(ecs_simple::Entity e:m_levelManager->GetEntities()){
        auto *level = m_levelManager->GetComponentByEntity(e);
        if(level->isCurrent){
            // get transform
            const auto *transform = m_transformsManager->GetComponentByEntity(e);

            // TraceLog(LOG_INFO,"%d %d",(int)transform->position.x,(int)transform->position.y);
            int parentTransformX = (int)transform->position.x;
            int parentTransformY = (int)transform->position.y;

            int counter = 0;

            for (int r = 0; r < level->matrix.rows; ++r) {
                for (int c = 0; c < level->matrix.cols; ++c) {

                    // create entity
                    ecs_simple::Entity tileEntity = p_registry->CreateEntity();

                    int newPosX = (c * level->tileWidth)  + parentTransformX;
                    int newPosY = (r * level->tileHeight) + parentTransformY;
                    // create primitive component
                    // m_transformsManager->Create(
                    //     tileEntity,
                    //     newPosX,newPosY
                    //     );

                    auto &tile = level->matrixTileMap(r,c);
                    DrawTile(tile.tileType,newPosX,newPosY,(counter % 2) == 0?0.96f:1.0f);
                    counter++;
                }
                counter++;
            }
        }
    }
}

// void LevelRenderSystem::LoadLevel()
// {
//     for(ecs_simple::Entity e:m_levelManager->GetEntities()){
//         auto *level = m_levelManager->GetComponentByEntity(e);
//         if(level->isCurrent){
//             // get transform
//             const auto *transform = m_transformsManager->GetComponentByEntity(e);

//             // TraceLog(LOG_INFO,"%d %d",(int)transform->position.x,(int)transform->position.y);
//             int parentTransformX = (int)transform->position.x;
//             int parentTransformY = (int)transform->position.y;

//             for (int r = 0; r < level->matrix.rows; ++r) {
//                 for (int c = 0; c < level->matrix.cols; ++c) {

//                     // if(level->matrix(r,c) == 0) continue;
//                     // map tilematrix
//                     level->matrixTileMap(r,c) = Tile{tileTypeMap[level->matrix(r,c)]};

//                     // create entity
//                     ecs_simple::Entity tileEntity = p_registry->CreateEntity();

//                     int newPosX = (c * level->tileWidth)  + parentTransformX;
//                     int newPosY = (r * level->tileHeight) + parentTransformY;
//                     // create primitive component
//                     m_transformsManager->Create(
//                         tileEntity,
//                         newPosX,newPosY
//                         );

//                     // TraceLog(LOG_INFO,"%d %d",newPosX,newPosY);
//                     auto &shape = m_shapesManager->Create(tileEntity,level->tileWidth,level->tileHeight,BLACK,RECTANGLE_LINE);
//                     shape.layer = TILE;

//                 }
//             }
//         }
//     }
// }

}
