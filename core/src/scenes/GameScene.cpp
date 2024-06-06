#include "GameScene.h"

#include "system/PrimitiveRenderSystem.h"
#include "system/LevelSystem.h"
#include "system/MovementCollisionSystem.h"
#include "ecs/ECSHelper.h"

namespace elementled {

GameScene::GameScene()
{

}

void GameScene::onCreate() {

    // register components
    m_registry->RegisterComponent<PrimitiveShapeComponent>();
    m_registry->RegisterComponent<InfoComponent>();
    m_registry->RegisterComponent<RelationshipComponent>();
    m_registry->RegisterComponent<TransformComponent>();
    m_registry->RegisterComponent<LevelComponent>();
    m_registry->RegisterComponent<KinematicBodyComponent>();

    // register system
    this->RegisterRenderSystem<PrimitiveRenderSystem>();
    this->RegisterRenderSystem<LevelSystem>();
    this->RegisterRenderSystem<MovementCollisionSystem>();
};

void GameScene::update(float dt)
{
    // TODO: implement pause
    Scene::update(dt);
}

void GameScene::render(float dt)
{
    Scene::render(dt);
    // //DrawText("GAME SCENE",50,50,30,BLACK);
    // // Scene::render(dt);
    // bool debug = false;

    // if(p_cameraComponent){
    //     BeginMode2D(p_cameraComponent->camera);
    //     // getRenderSystem<PrimitiveRenderSystem>()->update(dt);
    //     getRenderSystem<LevelSystem>()->update(dt);
    //     getRenderSystem<SpriteSystem>()->update(dt);
    //     if(debug){
    //         getRenderSystem<DebugRender>()->update(dt);
    //     }

    //     EndMode2D();
    // }else{
    //     // getRenderSystem<PrimitiveRenderSystem>()->update(dt);
    //     getRenderSystem<LevelSystem>()->update(dt);
    //     getRenderSystem<SpriteSystem>()->update(dt);
    //     if(debug){
    //         getRenderSystem<DebugRender>()->update(dt);
    //     }
    // }
    // getDrawSystem<ecs_simple::UiRenderSystem>()->update(dt);
    // getDrawSystem<ecs_simple::ImGuiRenderSystem>()->update(dt);
}

void GameScene::onActivate()
{
    // unsigned int archerTextureId =  s_context.textureResource->Add("/Assets/mainchar.png","archer");
    // unsigned int tilemapTextureId = s_context.textureResource->Add("/Assets/tilemap_packed_0.png","tilemap_01");
    // unsigned int aimUi = s_context.textureResource->Add("/Assets/aim360.png","aim_ui");


    // //-------------------------------------------------------------------------------------------------------------------------------
    // // player
    auto playerEntity = m_registry->CreateEntity();
    auto &transform = m_registry->CreateComponent<TransformComponent>(playerEntity,400,400);
    auto &primitiveShape = m_registry->CreateComponent<PrimitiveShapeComponent>(playerEntity,50,50,RED,RECTANGLE_LINE);
    auto &kinematic = m_registry->CreateComponent<KinematicBodyComponent>(playerEntity,200);
    kinematic.direction = {1,1};
    // level
    auto levelGameObject = CreateGameObject(m_registry,200,200);
    auto &level = m_registry->CreateComponent<LevelComponent>(levelGameObject.entity,10,10);
    level.tileWidth     = 60;
    level.tileHeight    = 60;
    level.matrix.mat = {
        1,1,1,1,1,1,1,1,1,1,
        1,1,0,0,0,0,0,0,0,1,
        1,0,1,0,0,0,0,0,0,1,
        1,0,0,0,0,0,0,0,0,1,
        1,0,0,0,0,0,0,0,0,1,
        1,0,0,0,0,0,0,0,0,1,
        1,0,0,0,0,0,0,0,0,1,
        1,0,0,0,0,0,0,0,0,1,
        1,0,0,0,0,0,0,0,0,1,
        1,1,1,1,1,1,1,1,1,1
    };

    level.isCurrent = true;

    // load level

    // auto playerEntity = ecs_simple::CreateEntity(m_registry,"player","player",math::Vec2f{20,20});
    // m_playerEntity = playerEntity.id;

    // // create sprite and add texture to component
    // auto &sprite = m_registry->createComponent<SpriteComponent>(playerEntity.id,archerTextureId);
    // sprite.setSpriteTiles(16,24,3,4);
    // sprite.setCurrentFrame(0);
    // sprite.renderLayer = RenderLayer::PLAYER;

    // auto &collider = m_registry->createComponent<ColliderComponent>(playerEntity.id,12,12);
    // collider.offset = {4.0f,10.0f};

    // auto &animator = m_registry->createComponent<AnimatorComponent>(playerEntity.id);
    // animator.AddAnimation("idle",4,7,8,true);
    // animator.AddAnimation("run",8,11,12,true);
    // animator.SetCurrentAnimation("idle");

    // // add kinematic body and player controller script
    // m_registry->createComponent<KinematicBodyComponent>(playerEntity.id,150.0f);
    // m_registry->createComponent<ScriptComponent>(playerEntity.id).bind<PlayerControllerScript>();

    // //-------------------------------------------------------------------------------------------------------------------------------
    // // camera
    // auto cameraEntity = m_registry->createEntity();
    // m_registry->createComponent<CameraComponent>(cameraEntity,m_playerEntity);
    // p_cameraComponent = m_registry->getComponent<CameraComponent>(cameraEntity);
    // p_cameraComponent->camera.zoom = 3;

    // // start the camera pointing at te target
    // auto ppos = m_registry->getComponent<TransformComponent>(playerEntity.id)->position;
    // Vector2 pos{ppos.x, ppos.y};
    // p_cameraComponent->camera.target = pos;


    // // m_registry->createComponent<ScriptComponent>(entity).bind<PlayerAnimatorScript>();
    // //-------------------------------------------------------------------------------------------------------------------------------
    // // environment
    // auto entityTilemap = ecs_simple::CreateEntity(m_registry,"world","world");

    // lazyDungeon::Dungeon dg(2,2,10,10);
    // dg.enableEntranceExit(true);
    // dg.init();

    // auto mat = dg.getMainRoom();

    // // // 2 entrance
    // // // 3 exit

    // auto& tilemap = m_registry->createComponent<TileMapComponent>(
    //     entityTilemap.id,
    //     mat.rows,
    //     mat.cols
    //     );

    // tilemap.active = true;
    // tilemap.tileSizeWidth   = 16;
    // tilemap.tileSizeHeight  = 16;

    // auto &tilemapSprite = m_registry->createComponent<SpriteComponent>(entityTilemap.id,tilemapTextureId);
    // tilemapSprite.setSpriteTiles(16,16,11,12);
    // tilemapSprite.setCurrentFrame(0);
    // tilemapSprite.renderLayer = RenderLayer::TILE;

    // tilemap.matrix.mat.resize(mat.mat.size());

    // for (int i = 0; i < mat.mat.size(); i++) {
    //     tilemap.matrix.mat[i] = static_cast<uint>(mat.mat[i]);
    // }

    // // tilemap.matrix.printMat();?.
    // //-------------------------------------------------------------------------------------------------------------------------------
    // // UI 8 DIRECTION
    // auto aimUiEntity = ecs_simple::CreateEntity(m_registry,"aim_ui","aim_ui",{0,0},playerEntity.id);

    // // auto& transformAimUI = m_registry->createComponent<TransformComponent>(aimUiEntity,0,0);
    // // aimUiEntity.transformComponent->scale = {0.5f,0.5f};
    // // // transformAimUI.rotation = 180;
    // aimUiEntity.transformComponent->localPosition = {-6,0};


    // auto& spriteAimUI = m_registry->createComponent<SpriteComponent>(aimUiEntity.id,aimUi);
    // // spriteAimUI.setSpriteTiles(54,54,1,1);
    // // spriteAimUI.setCurrentFrame(0);
    // spriteAimUI.renderLayer = RenderLayer::UI_GAMEPLAY;
    // spriteAimUI.pivot = {27*0.5,27*0.5};
    // spriteAimUI.alpha = 0.5f;

    // // auto &relationshipt = m_registry->createComponent<RelationshipComponent>(aimUiEntity,entity);

}
}
