#ifndef GAMESCENE_H
#define GAMESCENE_H

#include "Constants.h"
#include "Context.h"
#include "Scene.h"
// #include "ECS/Components/Components.h"


namespace elementled{

class GameScene: public Scene
{
public:
    GameScene();
    void onCreate() override;
    void onActivate() override;
    void update(float dt) override;
    void render(float dt) override;

private:
    ecs_simple::Entity m_playerEntity = ecs_simple::INVALID_ENTITY;
    // CameraComponent *p_cameraComponent = nullptr;
};

}
#endif // GAMESCENE_H
