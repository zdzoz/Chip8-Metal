//
//  Events.hpp
//  Chip8-Metal
//
//  Created by ザスキ・オスカー on 7/4/23.
//

#pragma once

#include <inttypes.h>

class Event;

enum class Key {
    ONE = 18,
    TWO = 19,
    THREE = 20,
    FOUR = 21,
    FIVE = 23,
    SIX = 22,
    SEVEN = 26,
    EIGHT = 28,
    NINE = 25,
    ZERO = 29,
    ESC = 53,
    A = 0,
    B = 11,
    C = 8,
    D = 2,
    E = 14,
    F = 3,
    L_ARR = 123,
    R_ARR = 124,
    U_ARR = 126,
    D_ARR = 125
};

enum class EventType {
    Null, KeyDown, KeyUp
};

class EventImplementation {
    friend Event;
    
    EventImplementation() {}
    
    uint64_t _keyCode;
    EventType _eventType;
public:
    void _setup(uint64_t keyCode, EventType eType);
    static EventImplementation* instance() {
        static EventImplementation* _instance = new EventImplementation;
        return _instance;
    }
};

class Event {
public:
    
    inline uint64_t keyCode() {
        return EventImplementation::instance()->_keyCode;
    }
    
    inline EventType eventType() {
        return EventImplementation::instance()->_eventType;
    }
};
