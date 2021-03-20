#pragma once
namespace graphics {
    struct Event {
        enum Type {
            Close,
            MouseButtonPressed,
            MouseButtonReleased,
            MouseWheelScrolled
        };
        enum MouseButton {
            Left,
            Right,
            Middle
        };
        Type type;
        MouseButton mouseButton;
        float mouseWheelScrollDelta;
        Event(Type t);
    };
}