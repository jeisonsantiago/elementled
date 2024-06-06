#ifndef CONTEXT_H
#define CONTEXT_H

#include "events/InputEventBus.h"
#include "resource/ResourceAllocator.h"

namespace elementled {


class Context{
public:
    static Context& getInstance(){
        static Context instance;
        return instance;
    }

    Context(const Context&) = delete;               // can't use those now
    Context& operator=(const Context&) = delete;    // ensure that only one instance exists

    std::unique_ptr<InputEventsBus> inputEventBus;
    std::unique_ptr<ResourceAllocator<ResourceSprite>> textureResource;

private:
    Context(){
        inputEventBus = std::make_unique<InputEventsBus>();
        textureResource = std::make_unique<ResourceAllocator<ResourceSprite>>();
    }
};
}


#endif // CONTEXT_H
