#include <stdio.h>
#include <stdlib.h>

#include "chip8main.h"
#include "emulator.h"

void ReadProgram(const char*, const unsigned char**, long*);

void start(const char* file_path) {
    const unsigned char* program = NULL;
    long programSize;
    ReadProgram(file_path, &program, &programSize);
    
    emulator(program, programSize);
    
    free((void*)program);
}

void ReadProgram(const char* loc, const unsigned char** program, long* programSize) {
    FILE* fp  = fopen(loc, "rb");
    if (fp == NULL) {
        printf("Could not read file\n");
        exit(-1);
    }
    printf("filepath: %s\n", loc);
    fseek(fp, 0L, SEEK_END);
    *programSize = ftell(fp);
    rewind(fp);
    printf("filesize: %ld bytes\n", *programSize);
    
    *program = (unsigned char*)malloc(*programSize + 1);
    fread((void*)*program, sizeof(char), *programSize, fp);
    fclose(fp);
}
