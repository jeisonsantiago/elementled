#ifndef ECSSIMPLE_H
#define ECSSIMPLE_H

namespace ecs_simple {

using Entity = uint32_t;
static const Entity INVALID_ENTITY = -1;

class ComponentManagerBase{
public:
    virtual void RemoveEntity(Entity entity) = 0;
};

template<typename Component>
class ComponentManager : public ComponentManagerBase

{
private:
    std::vector<Component> components;
    std::vector<Entity> entities;
    std::unordered_map<Entity, size_t> lookup;
    bool m_multipleComponents = false;
public:

    ComponentManager() = default;
    ComponentManager(bool multiple):m_multipleComponents(multiple){};

    std::vector<Component>& GetComponentVector(){
        return components;
    }

    bool Contains(Entity entity) const
    {
        return lookup.find(entity) != lookup.end();
    }

    // Create component with support to multiple arguments as second parameter
    template <typename ...T>
    Component& Create(Entity entity, T&& ...arg)
    {
        // INVALID_ENTITY is not allowed!
        assert(entity != INVALID_ENTITY);

        if(!m_multipleComponents){
            // Only one of this component type per entity is allowed!
            assert(lookup.find(entity) == lookup.end());
        }

        // Entity count must always be the same as the number of components!
        assert(entities.size() == components.size());
        assert(lookup.size() == components.size());

        // Update the entity lookup table:
        lookup[entity] = components.size();

        entities.push_back(entity);

        // New components are always pushed to the end:
        return components.emplace_back(Component(std::forward<T>(arg)...));
    }

    size_t GetCount() const { return components.size(); }
    Component& operator[](size_t index) { return components[index]; }
    Entity GetEntity(size_t index) const { return entities[index]; }

    std::vector<Entity> const &GetEntities() {return entities;};


    inline Component* GetComponentByIndex(size_t index)
    {
        if(index >= 0 || index < components.size()) return &components[index];
        return nullptr;
    }

    inline Component* GetComponentByEntity(Entity entity)
    {
        auto it = lookup.find(entity);
        if (it != lookup.end())
        {
            return &components[it->second];
        }
        return nullptr;
    }

    inline Component* GetComponentByEntityNoCheck(Entity entity)
    {
        return &components[lookup[entity]];
    }


    inline void RemoveEntity(Entity entity) override
    {
        auto it = lookup.find(entity);
        if (it != lookup.end())
        {
            // Directly index into components and entities array:
            const size_t index = it->second;
            const Entity entity = entities[index];

            if (index < components.size() - 1)
            {
                // Swap out the dead element with the last one:
                components[index] = std::move(components.back()); // try to use move
                entities[index] = entities.back();

                // Update the lookup table:
                lookup[entities[index]] = index;
            }

            // Shrink the container:
            components.pop_back();
            entities.pop_back();
            lookup.erase(entity);
        }
    }
};

// registry works as a basket of ComponentManagers
class Registry{
public:

    Registry() = default;

    template<typename T>
    void RegisterComponent(){
        m_AllComponents[typeid(T).name()] = std::make_shared<ComponentManager<T>>();
    }

    template<typename T>
    void RegisterComponent(bool multiple){
        m_AllComponents[typeid(T).name()] = std::make_shared<ComponentManager<T>>(multiple);
    }

    template<typename T>
    std::vector<T> &GetComponentVector(){
        assert((m_AllComponents.count(typeid(T).name()) != 0) && "Component must be registered.");
        std::shared_ptr<ComponentManager<T>> c = std::static_pointer_cast<ComponentManager<T>>(m_AllComponents[typeid(T).name()]);
        return c->getComponentVector();
    }

    template<typename T>
    std::shared_ptr<ComponentManager<T>> GetComponentManager(){
        assert((m_AllComponents.count(typeid(T).name()) != 0) && "Component must be registered.");
        return std::static_pointer_cast<ComponentManager<T>>(m_AllComponents[typeid(T).name()]);
    }

    template<typename T>
    void RemoveEntityComponent(Entity e){
        assert((m_AllComponents.count(typeid(T).name()) != 0) && "Component must be registered.");
        std::shared_ptr<ComponentManager<T>> c = std::static_pointer_cast<ComponentManager<T>>(m_AllComponents[typeid(T).name()]);
        c->RemoveEntity(e);
    }

    // remove entity from all ComponentManager registered (if available)
    void RemoveEntity(Entity e){
        m_Entities.erase(e);
        //JENGINE_INFO("Remove Entity:%d",e);
        for(auto&[key, value] : m_AllComponents){
            if(!value) continue; // if ComponentManager is registered but does not hold any entity continue
            value->RemoveEntity(e);
        }
    }

    template<typename T, typename ...H>
    T& CreateComponent(Entity e, H&&... arg){
        //m_entities.insert(e);
        auto cmanager = GetComponentManager<T>();
        return cmanager->Create(e,T(std::forward<H>(arg)...));
    }

    template<typename T>
    T* getComponent(Entity e){
        auto cmanager = GetComponentManager<T>();
        return cmanager.get()->GetComponentByEntity(e);
    }

    std::set<Entity> &GetEntities(){
        return m_Entities;
    }

    Entity CreateEntity()
    {
        m_Entities.insert(next+1);
        next+=1;

        // check common component managers
        return next;
    }

private:
    std::unordered_map<std::string, std::shared_ptr<ComponentManagerBase>> m_AllComponents;
    std::set<Entity> m_Entities;
    Entity next = 0;
};
}
#endif // ECSSIMPLE_H
