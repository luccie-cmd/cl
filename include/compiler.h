#pragma once
#include <assert.h>
#include "common.h"
#include "mystring.h"

typedef struct{
    Inst program[STACK_MAX];
    size_t program_size;
} Compiler;

void compiler_print_program(const Compiler *com);
void compiler_add_to_program(Compiler *com, Inst item);
void compiler_load_program_from_file(Compiler *com, const char* path);
void compiler_write_to_file(Compiler *com, const char *path);