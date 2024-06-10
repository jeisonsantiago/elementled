#ifndef TILES_H
#define TILES_H

#include "raylib.h"
#include "Constants.h"

namespace elementled {

enum TileType{
    WATER = 0,
    STONE_WALL = 1,
    GRASS_GREEN = 2, // usualy solids
    DIRT = 3,
};

static std::unordered_map<int, TileType> tileTypeMap = {
    {0,WATER},
    {1,STONE_WALL},
    {2,GRASS_GREEN},
    {3,DIRT},
};


struct Tile{
    TileType tileType = GRASS_GREEN;
    Tile() = default;
    Tile(TileType t):tileType(t){};
};

static void DrawTile(const TileType& tileType, float x, float y, float alpha = 1){

    switch (tileType) {
    case WATER:
        DrawRectangle(
            x,
            y,
            TILE_WIDTH,
            TILE_HEIGHT,
            ColorAlpha(BLUE,alpha));
        break;
    case GRASS_GREEN:
        DrawRectangle(
            x,
            y,
            TILE_WIDTH,
            TILE_HEIGHT,
            ColorAlpha(GREEN,alpha));
        break;
    case STONE_WALL:
        DrawRectangle(
            x,
            y,
            TILE_WIDTH,
            TILE_HEIGHT,
            ColorAlpha(GRAY,alpha));
        break;
    }
}

}

#endif // TILE_H
