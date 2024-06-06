#ifndef DEFINITIONS_H
#define DEFINITIONS_H

namespace elementled {
enum Shape{
    CIRCLE,
    CIRCLE_LINE,
    RECTANGLE,
    RECTANGLE_LINE,
};

enum BodyType{
    STATIC,
    DYNAMIC,
};

enum RenderLayer{
    DEFAULT = 0,
    BACKGROUND = 1,
    TILE = 2,
    PLAYER = 3,
    ENEMY = 4,
    PROJECTILES = 5,
    FOREGROUND = 6,
    UI_GAMEPLAY = 7,
};

enum CollisionLayer{
    DEFAULT_COLLISION = 0,
    TILE_COLLISION = 2,
    PLAYER_COLLISION = 3,
    ENEMY_COLLISION = 4,
    TRIGGER_COLLISION = 4,
    PROJECTILES_COLLISION = 5,
};
}

#endif // DEFINITIONS_H
