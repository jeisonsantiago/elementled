#include "InputEventBus.h"

#include "Events.h"

namespace elementled {

void InputEventsBus::mouseButtonEvents(int button){}

void InputEventsBus::mouseMoveEvents(int button){}

void InputEventsBus::KeyPressEvents(){
    // quit key
    if(IsKeyPressed(KEY_ESCAPE)){
        m_eventDispatcher.post<QuitEvent>();
        LAME_INFO("<quit_event>");
    }

    if(IsKeyPressed(KEY_P)){
        m_eventDispatcher.post<PauseEvent>();
        LAME_INFO("<pause_event>");
    }

    m_eventDispatcher.dispatch();
}

void InputEventsBus::DispatchEvents()
{
    // keyboard events
    this->KeyPressEvents();

    // mouse position
    // auto pos = GetMousePosition();
    // // compare and emit
    // if (m_mouse.offset.x != pos.x || m_mouse.offset.y != pos.y){
    //     m_input_dispatcher.post<mouse_motion_event>();
    // }
    // m_mouse.offset = {pos.x, pos.y};

    // auto wheel = GetMouseWheelMoveV();
    // // compare and emit
    // if (m_mouse.wheel.x != wheel.x || m_mouse.wheel.y != wheel.y){
    //     m_input_dispatcher.post<mouse_wheel_event>();
    // }
    // m_mouse.wheel = {wheel.x, wheel.y};

}


}
