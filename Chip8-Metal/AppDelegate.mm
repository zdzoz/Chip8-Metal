//
//  AppDelegate.m
//  GameObjc
//
//  Created by ザスキ・オスカー on 6/22/23.
//

#import "AppDelegate.h"
#import "chip8main.h"
#include <thread>

extern bool isEmulatorRunning;

@interface AppDelegate ()

@end

@implementation AppDelegate {
    const unsigned char* program;
    std::thread emu;
}

- (void)applicationDidFinishLaunching:(NSNotification *)aNotification {
    emu = std::thread(start, [NSString stringWithFormat:@"%@%s", NSBundle.mainBundle.resourcePath, "/roms/breakout.ch8"].UTF8String);
}

- (void)applicationWillTerminate:(NSNotification *)notification {
    isEmulatorRunning = FALSE;
    emu.join();
}

- (BOOL)applicationShouldTerminateAfterLastWindowClosed:(NSApplication *)sender {
    return YES;
}

@end
