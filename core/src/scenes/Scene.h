#ifndef SCENE_H
#define SCENE_H

#include "ecs/ECSSimple.h"
#include "system/System.h"

namespace elementled {

class Scene
{
public:
    Scene();
    virtual ~Scene() = default; // if [default] was [0] needs implementation

    virtual void onCreate(){};

    virtual void onDestroy(){};

    virtual void onActivate(){};

    virtual void onDeactivate(){};

    virtual void update(float dt) = 0;

    virtual void render(float dt) = 0;

    // TODO: remove system
    template <typename T>
    T* RegisterSystem(){
        static_assert(std::is_base_of<System, T>::value);
        auto s = std::make_shared<T>();
        m_systems[typeid(T).name()] = s;
        s.get()->Prepare(m_registry.get());
        //m_systems.end()->second->prepare(m_registry.get(), m_game_event_dispatcher.get());
        m_systemOrderedKeys.push_back(typeid(T).name());
        // s.get()->start();
        return s.get();
    }

    template <typename T>
    T* RegisterRenderSystem(){
        static_assert( std::is_base_of<System, T>::value);
        auto s = std::make_shared<T>();
        m_renderSystems[typeid(T).name()] = s;
        s.get()->Prepare(m_registry.get());
        //m_systems.end()->second->prepare(m_registry.get(), m_game_event_dispatcher.get());
        m_renderSystemOrderedKeys.push_back(typeid(T).name());
        return s.get();
    }

    template <typename T>
    System* GetSystem(){
        auto it = m_systems.find(typeid(T).name());
        if(it != m_systems.end()){
            return it->second.get();
        }

        return nullptr;
    }

    template <typename T>
    System* GetRenderSystem(){
        auto it = m_renderSystems.find(typeid(T).name());
        if(it != m_renderSystems.end()){
            return it->second.get();
        }

        return nullptr;
    }

    std::shared_ptr<ecs_simple::Registry> GetRegistry(){
        return m_registry;
    }

protected:
    // all scenes has it's own set of systems
    std::unordered_map<std::string, std::shared_ptr<System>> m_systems;
    std::unordered_map<std::string, std::shared_ptr<System>> m_renderSystems;
    std::vector<std::string> m_systemOrderedKeys;
    std::vector<std::string> m_renderSystemOrderedKeys;

    //all scenes holds a registry
    std::shared_ptr<ecs_simple::Registry> m_registry;
    // Context& s_context = Context::getInstance();
    // std::shared_ptr<ecs_simple::Registry> m_eventBus;
    // SharedContext* m_sharedContext = nullptr;
    // std::shared_ptr<ResourceAllocator<ResourceSprite>> m_textureResource;
};

}

#endif // SCENE_H
