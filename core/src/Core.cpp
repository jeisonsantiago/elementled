#include "Core.h"

#include "Context.h"
#include "events/Events.h"
#include "scenes/GameScene.h"

namespace elementled{

static bool isRunning = true;

void PrintHelloWorld()
{
    std::cout << "Hello Core!\n";
}

// create application function that returns configuration
appConfig CreateApplication()
{
    appConfig config;
    config.version = "0.0.1";
    config.title = "Elementled";
    config.height = 720*2;
    config.width = 1080*2;
    return config;
}

void RunApplication(const appConfig &config)
{
    // init Context
    // context::inputEventBus = new InputEventsBus();
    // context::textureResource = new ResourceAllocator<ResourceSprite>();
    // context::initialize();
    Context& context = Context::getInstance();

    // set up shared context
    // std::shared_ptr<SharedContext> context = std::make_shared<SharedContext>();

    // set up resource allocator
    // context->textureResource = std::make_unique<ResourceAllocator<ResourceSprite>>();

    // input event bus
    // context->inputEventBus = std::make_unique<InputEventsBus>();

    // set QuitEvent
    context.inputEventBus->GetEventDispatcher().add_callback<QuitEvent>([](const QuitEvent &e){
        isRunning = false;
        return true;
    });

    // SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_RESIZABLE);
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    // set up window
    InitWindow(config.width, config.height,config.title.c_str());

    SetTargetFPS(120);

    // main scene manager
    // std::unique_ptr<SceneManager> sceneManager= std::make_unique<SceneManager>();
    // // set game scene and add to scene manager
    // std::shared_ptr<GameScene> gameScene = std::make_shared<GameScene>();
    // sceneManager->AddScene("game",gameScene);
    // sceneManager->SwitchTo("game");
    std::unique_ptr<GameScene> gameScene = std::make_unique<GameScene>();
    gameScene->onCreate();
    gameScene->onActivate();

    SetExitKey(0);

    // main game loop
    while (isRunning) {

        // dispatch events
        context.inputEventBus->DispatchEvents();

        // update scene
        // sceneManager->GetCurrentScene()->update(GetFrameTime());
        float dt = GetFrameTime();
        gameScene->update(dt);

        // render
        BeginDrawing();

        ClearBackground(BLACK);

        // sceneManager->GetCurrentScene()->render(GetFrameTime());
        gameScene->render(dt);

        int fps = GetFPS();
        std::string fpsStr = "FPS:\t";
        fpsStr.append(std::to_string(fps));
        DrawText(fpsStr.c_str(),19,19,30,WHITE);
        // DrawText(fpsStr.c_str(),20,20,20,BLACK);

        EndDrawing();
    }

    CloseWindow();
}

}

