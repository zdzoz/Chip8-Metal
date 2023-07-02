//
// Created by Oskar Zdziarski on 3/31/23.
//

#ifndef CHIP8_EMULATOR_H
#define CHIP8_EMULATOR_H

#include "stack.h"

typedef uint8_t byte;

typedef struct {
    uint32_t pc;
    uint16_t I; // I registers
    byte v[16]; //  V registers
    byte DT, ST; // Delay & Sound Timer
    Stack* sp; // Stack Pointer
    unsigned char memory[0xfff];
} State;

void emulator(const unsigned char *program, long programSize);

uint32_t emulateCPU();

int disassemble();

void handle_input();

#endif //CHIP8_EMULATOR_H
