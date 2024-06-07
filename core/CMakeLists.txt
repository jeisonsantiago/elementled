project(core VERSION 0.0.1)

#get all cpp files
set(SRC_FILES
    src/Definitions.h

    src/pch.h
    src/pch.cpp

    src/Core.h
    src/Core.cpp

    src/ecs/ECSSimple.h
    src/ecs/ECSSimple.cpp
    src/ecs/ECSHelper.h

    src/math/Matrix.h
    src/math/Vec2.h

    src/scenes/Scene.h
    src/scenes/Scene.cpp
    src/scenes/GameScene.h
    src/scenes/GameScene.cpp

    src/system/System.h
    src/system/PrimitiveRenderSystem.h
    src/system/PrimitiveRenderSystem.cpp
    src/system/LevelSystem.h
    src/system/LevelSystem.cpp
    src/system/MovementCollisionSystem.h
    src/system/MovementCollisionSystem.cpp
    src/system/PlayerMovementSystem.h
    src/system/PlayerMovementSystem.cpp

    src/events/Event.h
    src/events/Events.h
    src/events/EventDispatcher.h
    src/events/InputEventBus.h
    src/events/InputEventBus.cpp

    src/Context.h

    src/components/Components.h

)

add_library(${PROJECT_NAME} ${SRC_FILES}



    )

include_directories(${CMAKE_SOURCE_DIR}/core/src)

if(UNIX)
    # add raylib
    find_library(LIB_RAYLIB raylib ${CMAKE_SOURCE_DIR}/vendor/linux/raylib)

    if(NOT LIB_RAYLIB)
        message(${CMAKE_SOURCE_DIR}/vendor/linux/raylib)
        message(FATAL_ERROR "raylib library not found")
    endif()

    # ----- INCLUDES ----
    target_include_directories(
        ${PROJECT_NAME} PUBLIC ${CMAKE_SOURCE_DIR}/vendor/linux/raylib/include
    )

    # target_link_libraries(${PROJECT_NAME} ${LIB_RAYLIB} ${LIB_BOX2D})
    target_link_libraries(${PROJECT_NAME} ${LIB_RAYLIB})

endif()

target_precompile_headers(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src/pch.h)


