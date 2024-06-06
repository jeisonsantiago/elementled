#ifndef ECS_SYSTEM_H
#define ECS_SYSTEM_H

#include "ecs/ECSSimple.h"

namespace elementled{

class System{
public:

    System() = default;

    virtual ~System(){
        p_registry = nullptr;

    };

    virtual void Prepare(ecs_simple::Registry *r){

        // check if p_registry is valid
        assert(r != nullptr && "p_registry must be a valid pointer");
        p_registry = r;
    }

    virtual void Update(float dt){}
    virtual void Start(){}

protected:
    ecs_simple::Registry *p_registry = nullptr;
    // Context &s_context = Context::getInstance();
};

}
#endif // ECS_SYSTEM_H
