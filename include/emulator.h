#pragma once
#include <assert.h>
#include "common.h"

typedef struct{
    Word stack[STACK_MAX];
    Word stack_size;
    Inst program[PROGRAM_MAX];
    size_t program_size;
    int halted;
    size_t program_ip;
} Emulator;

void emulator_print_program(const Emulator *emu);
void emulator_print_stack(const Emulator *emu);
void emulator_add_to_stack(Emulator *emu, Word item);
void emulator_add_to_program(Emulator *emu, Inst item);
void emulator_load_program_from_file(Emulator *emu, const char* path);
Err emulator_execute_program(Emulator *emu);