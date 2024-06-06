#ifndef EVENTS_H
#define EVENTS_H

#include "Event.h"

namespace elementled {

struct QuitEvent: EventInstance{
    QuitEvent() = default;
};

struct PauseEvent: EventInstance{
    PauseEvent() = default;
};


struct KeyEvent: EventInstance{
    int key;
    bool pressed;
    KeyEvent(int key, int pressed):key(key),pressed(pressed){};
};

struct KeydownEvent:EventInstance{
    int key;
    KeydownEvent(int key):key(key){};
};


struct KeydownPressedEvent: EventInstance{
    int key;
    KeydownPressedEvent(int key):key(key){};
};

struct KeyUpEvent: EventInstance{
    int key;
    KeyUpEvent(int key):key(key){};
};

struct MouseButtonDownEvent: EventInstance{
    int button;
    MouseButtonDownEvent(int button):button(button){};
};

struct MouseButtonUpEvent: EventInstance{
    int button;
    MouseButtonUpEvent(int button):button(button){};
};

struct MouseMotionEvent: EventInstance{
    MouseMotionEvent() = default;
};

struct MouseWheelEvent: EventInstance{
    MouseWheelEvent() = default;
};
}

#endif // EVENTS_H
