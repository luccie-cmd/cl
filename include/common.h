#pragma once
#define STACK_MAX 1024
#define PROGRAM_MAX 1024
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#define VERSION_MAJOR 0
#define VERSION_MINOR 1
#define VERSION_PATCH 1

typedef uint64_t Word;
typedef enum{
    INST_PUSH=0,
    INST_PLUS,
    INST_HALT,
} Inst_Types;
typedef enum{
    ERR_OK=0,
    ERR_OVERFLOW,
    ERR_UNDERFLOW,
    ERR_ILLEGAL_INST,
    ERR_ILLEGAL_INST_ACCESS,
} Err;
typedef struct{
    Inst_Types type;
    Word operand;
} Inst;

uint8_t *slurp_file_bin(const char* path);
char *err_as_cstr(Err err);
Inst make_inst_push(Word operand);
Inst make_inst_plus();
Inst make_inst_halt();
char *inst_type_as_cstr(Inst_Types type);
int check_extention(char *path, char *extention);