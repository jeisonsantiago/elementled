#ifndef COMPONENTS_H
#define COMPONENTS_H

#include "Definitions.h"
#include "math/Matrix.h"
#include "math/Vec2.h"
#include "ecs/ECSSimple.h"

namespace elementled{
// -------------------------------------------------------------------------
struct InfoComponent{
    std::string name = "entity";
    std::string tag = "default";
    bool isActive = true;
    bool queueFree = false;
    uuid64 uuid = generateUUID();

    InfoComponent() = default;
    InfoComponent(const InfoComponent&) = default;
    InfoComponent(const std::string& n, const std::string& t):name(n),tag(t){};
};

struct RelationshipComponent{
    size_t children = 0;
    ecs_simple::Entity first_child = ecs_simple::INVALID_ENTITY;
    ecs_simple::Entity next_sibling = ecs_simple::INVALID_ENTITY;
    ecs_simple::Entity parent = ecs_simple::INVALID_ENTITY;

    RelationshipComponent() = default;
    RelationshipComponent(const RelationshipComponent&) = default;
    RelationshipComponent(ecs_simple::Entity p):parent(p){};
};
// -------------------------------------------------------------------------
struct PrimitiveShapeComponent{
    Shape type = CIRCLE;
    float radius;
    float width, height;
    Color color = RED;
    RenderLayer layer = DEFAULT;


    PrimitiveShapeComponent(float r, Color c = RED,Shape s = CIRCLE):radius(r){
        type = s;
        color = c;
    }

    PrimitiveShapeComponent(float w, float h, Color c = RED,Shape s = RECTANGLE):width(w),height(h){
        type = s;
        color = c;
    }
};
// -------------------------------------------------------------------------
struct TransformComponent{
    math::Vec2f position = {0,0};
    math::Vec2f localPosition = {0,0};
    math::Vec2f scale = {1,1};
    float rotation = 0;

    TransformComponent() = default;

    TransformComponent(float x, float y){
        position.x = x;
        position.y = y;
    }

    TransformComponent(float x, float y, float xPivot, float yPivot){
        position = {x,y};
        localPosition = {xPivot, yPivot};
    }

    TransformComponent(const TransformComponent&) = default;
};
// -------------------------------------------------------------------------
struct LevelComponent{
    bool isCurrent = false;
    size_t levelIndex = 0;
    size_t rowsCount = 0;
    size_t colsCount = 0;
    size_t tileWidth = 0;
    size_t tileHeight = 0;
    math::Matrix<uint> matrix;

    LevelComponent(size_t r, size_t c):rowsCount(r),colsCount(c){
        matrix = math::Matrix<uint>(r,c,0);
    }

    uint operator()(size_t row, size_t col) const{
        return matrix(row,col);
    };

    uint &operator()(size_t row, size_t col) {
        return matrix(row,col);
    };
};

// -------------------------------------------------------------------------
struct TileMapComponent{
    size_t index = 0;
    size_t rows = 0;
    size_t cols = 0;
    Color tileColor = BROWN;
    bool active = false;
    // tilemap_size tile_size= {0,0};
    size_t tileSizeWidth = 0;
    size_t tileSizeHeight = 0;
    math::Matrix<uint> matrix;
    math::Matrix<uint> matrixCoded;

    // tile code, tile number
    std::map<uint, size_t> tilemapCodeIndex;

    TileMapComponent(size_t r, size_t c):rows(r),cols(c){
        matrix = math::Matrix<uint>(r,c,0);
    }

    TileMapComponent(size_t r, size_t c, Color cl):rows(r),cols(c),tileColor(cl){
        matrix = math::Matrix<uint>(r,c,0);
    }

    uint operator()(size_t row, size_t col) const{
        return matrix(row,col);
    };

    uint &operator()(size_t row, size_t col) {
        return matrix(row,col);
    };

    math::Vec2f dungeonEntrance(uint code = 2){
        for (int r = 0; r < rows; ++r) {
            for (int c = 0; c < cols; ++c) {
                if(matrix(r,c) == code){
                    return {
                            r*static_cast<float>(this->tileSizeHeight),
                            c*static_cast<float>(this->tileSizeWidth)};
                }
            }
        }

        return {-1.0f,-1.0f};
    };

    math::Vec2f dungeonExit(uint code = 2){ return math::Vec2f(0,0);};


    // tiles colliding
    bool rect_colliding_tiles(float x, float y, float w, float h){

        float left = x;
        float right = x+w;
        float top = y;
        float bottom = y+h;

        int left_tile = (left / tileSizeWidth);
        int right_tile = (right / tileSizeWidth);
        int top_tile = (top / tileSizeHeight);
        int bottom_tile = (bottom / tileSizeHeight);

        // check boundaries
        // if(left_tile < 0) left_tile = 0;
        // if(top_tile < 0) top_tile = 0;
        // if(right_tile > tileSizeWidth) right_tile = tileSizeWidth;
        // if(bottom_tile > tileSizeHeight) bottom_tile = tileSizeHeight;

        // TODO: cap values
        bool any_collision = false;
        for(size_t i = left_tile; i <= right_tile;i++){
            for(size_t j = top_tile; j <= bottom_tile;j++){
                int tile_value = this->operator()(j,i);
                if(tile_value == 1){
                    any_collision = true;
                }
            }
        }

        return any_collision;
    }
};
// -------------------------------------------------------------------------
struct KinematicBodyComponent{
    // rigid body
    float speed = 0.0f;
    math::Vec2<float> acceleration = 0.0f;
    math::Vec2<float> direction = {0.0f,0.0f};
    math::Vec2<float> oldDirection = {0.0f,0.0f};

    KinematicBodyComponent(float s):speed(s){}
};
}

#endif // COMPONENTS_H
