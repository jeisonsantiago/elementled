#ifndef EVENT_H
#define EVENT_H

namespace elementled {

using eventId = uint32_t;


// declare main instance event so other events can inherit from it
struct EventInstance{
    virtual ~EventInstance() = default;
};

// callback using lambda, std::function<bool(const T&)> is a
// signature function with return bool and generic type as parameter
template<typename T>
using CallbackFunction = std::function<bool(const T&)>;

// generic callback instance to be used as base struct for new events callback
struct CallbackInstance {
    virtual ~CallbackInstance() = default;
    virtual bool run(EventInstance *) = 0;
};


template<typename T>
struct EventCallback : CallbackInstance{
    EventCallback(CallbackFunction<T>& call){
        callback = call;
    }

    bool run(EventInstance *e){
        auto data = static_cast<const T&>(*e);
        return callback(data); // run "generic function"
    }

private:
    CallbackFunction<T> callback;
};

using CallbackList = std::vector<std::shared_ptr<CallbackInstance>>;

}

#endif // EVENT_H
