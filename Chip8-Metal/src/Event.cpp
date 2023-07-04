//
//  Events.cpp
//  Chip8-Metal
//
//  Created by ザスキ・オスカー on 7/4/23.
//

#include "Event.hpp"

void EventImplementation::_setup(uint64_t keyCode, EventType eType) {
    this->_keyCode = keyCode;
    this->_eventType = eType;
}

