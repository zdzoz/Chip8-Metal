//
//  Events.m
//  Chip8-Metal
//
//  Created by ザスキ・オスカー on 7/4/23.
//

#import "GameView.h"

#include "Event.hpp"

@implementation GameView

-(BOOL)acceptsFirstResponder {
    return YES;
}

-(void)keyDown:(NSEvent *)event {
    EventImplementation::instance()->_setup(event.keyCode, EventType::KeyDown);
    [super keyDown:event];
}

-(void)keyUp:(NSEvent *)event {
    EventImplementation::instance()->_setup(event.keyCode, EventType::KeyUp);
    [super keyUp:event];
}

@end
