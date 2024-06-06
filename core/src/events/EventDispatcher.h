#ifndef EVENTDISPATCHER_H
#define EVENTDISPATCHER_H


#include "Event.h"
#include "TypeId.h"



namespace elementled {

struct EventDispatcher{

    // post event with the type T, with the necessary arguments Args...
    template<typename T, typename... Args>
    void post(Args&&...args){
        static_assert(std::is_base_of<EventInstance,T>::value);

        _events[TypeID()] = new T(std::forward<Args>(args)...);
    }

    //register callback for the event of type T
    template <typename T>
    void add_callback(CallbackFunction<T>&& call){
        static_assert(std::is_base_of<EventInstance,T>::value);

        auto entry = std::make_shared<EventCallback<T>>(call);
        _callbacks[TypeID()].push_back(entry);
    }

    // handle events and keep memory pool clean after dispatching all
    void dispatch(){
        if(!_events.size()){return;} // if there's no event exit loop

        for(auto &[code, entry]: _events){
            for(auto &clbk :_callbacks[code]){
                if(clbk->run(entry)){break;}
            }
        }

        for(auto ev:_events){
            LAME_DELETE(ev.second);
        }

        _events.clear();
    }

    ~EventDispatcher(){
        for(auto ev:_events){
            LAME_DELETE(ev.second);
        }

        _events.clear();
        _callbacks.clear();
    }

private:
    std::unordered_map<eventId, EventInstance*> _events;
    std::unordered_map<eventId, CallbackList> _callbacks;
};
}

#endif // EVENTDISPATCHER_H
