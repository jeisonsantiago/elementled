#include "PrimitiveRenderSystem.h"

namespace elementled {

struct ShapeAndTransform{
    PrimitiveShapeComponent *shape = nullptr;
    TransformComponent *transform = nullptr;
};

PrimitiveRenderSystem::PrimitiveRenderSystem() {}

void PrimitiveRenderSystem::Prepare(ecs_simple::Registry *registry)
{
    // call parent class prepare()
    System::Prepare(registry);

    // get necessary component managers
    m_transformsManager = p_registry->GetComponentManager<TransformComponent>();
    m_shapesManager = p_registry->GetComponentManager<PrimitiveShapeComponent>();
}

void PrimitiveRenderSystem::Update(float dt)
{
    bool drawCollider = false;

    // organize the current render frame by layers
    std::map<RenderLayer, std::vector<ShapeAndTransform>> layerVector;

    for(ecs_simple::Entity e:m_shapesManager->GetEntities()){
        auto *shape = m_shapesManager->GetComponentByEntity(e);
        auto *transform = m_transformsManager->GetComponentByEntity(e);

        // we need both to be valid so we can render
        if(!shape || !transform) continue;

        layerVector[shape->layer].emplace_back(ShapeAndTransform{shape,transform});
    }


    for(auto& item:layerVector){
        for(auto& st:item.second){
            Color collidingColor = st.shape->color;

            //TODO: draw collider
            switch (st.shape->type) {
            case Shape::CIRCLE:{
                DrawCircle(
                    st.transform->position.x,
                    st.transform->position.y,
                    st.shape->radius,
                    collidingColor);
                break;
            }
            case Shape::CIRCLE_LINE:{
                DrawCircleLines(
                    st.transform->position.x,
                    st.transform->position.y,
                    st.shape->radius,
                    collidingColor);
                break;
            }
            case Shape::RECTANGLE:{
                DrawRectangle(
                    st.transform->position.x,
                    st.transform->position.y,
                    st.shape->width,
                    st.shape->height,
                    collidingColor);
                break;
            }
            case Shape::RECTANGLE_LINE:{
                DrawRectangleLines(
                    st.transform->position.x,
                    st.transform->position.y,
                    st.shape->width,
                    st.shape->height,
                    collidingColor);
                break;
            }
            default:
                break;
            }


        }
    }

}
}
