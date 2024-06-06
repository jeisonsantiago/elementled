#ifndef INPUTEVENTBUS_H
#define INPUTEVENTBUS_H

#include "EventDispatcher.h"
#include "math/Vec2.h"

namespace elementled {

struct MouseState{
    std::bitset<7> buttons = {0};
    math::Vec2<float> offset;
    math::Vec2<float> wheel;
};

class InputEventsBus
{
public:
    InputEventsBus() = default;
    void DispatchEvents();
    EventDispatcher &GetEventDispatcher(){return m_eventDispatcher;}

private:
    void mouseButtonEvents(int button);
    void mouseMoveEvents(int button);
    void KeyPressEvents();

    EventDispatcher m_eventDispatcher;
    MouseState m_mouseState;

};

}


#endif // INPUTEVENTBUS_H
