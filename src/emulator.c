#include "emulator.h"

void emulator_print_program(const Emulator *emu){
    printf("program:\n");
    if(emu->program_size == 0){
        printf("    [EMPTY]");
    }
    for(size_t i = 0; i < emu->program_size; ++i){
        printf("    type = %s operand = %lld\n", inst_type_as_cstr(emu->program[i].type), emu->program[i].operand);
    }
}

void emulator_print_stack(const Emulator *emu){
    printf("stack:\n");
    if(emu->stack_size == 0){
        printf("    [EMPTY]");
    }
    for(size_t i = 0; i < emu->stack_size; ++i){
        printf("    %lld\n", emu->stack[i]);
    }
}

void emulator_add_to_stack(Emulator *emu, Word item){
    assert(emu->stack_size < STACK_MAX);
    emu->stack[emu->stack_size++] = item;
}

void emulator_add_to_program(Emulator *emu, Inst item){
    assert(emu->program_size < PROGRAM_MAX);
    emu->program[emu->program_size++] = item;
}

void emulator_load_program_from_file(Emulator *emu, const char* path){
    uint8_t* content = slurp_file_bin(path);
    if(content == NULL) exit(1);
    int i = 0;
    int halt = 0;
    while(!halt){
        switch(content[i++]){
            case INST_PUSH: {
                Word operand = content[i++];
                emulator_add_to_program(emu, make_inst_push(operand));
            } break;
            case INST_PLUS: {
                emulator_add_to_program(emu, make_inst_plus());
            } break;
            case INST_HALT: {
                emulator_add_to_program(emu, make_inst_halt());
                halt = 1;
            } break;
            default: { 
                printf("Invalid inst named: %c\n", content[i-1]);
                exit(1);
            } break;
        }
    }
}

Err emulator_execute_program(Emulator *emu){
    while(!emu->halted){
        switch(emu->program[emu->program_ip].type){
            case INST_PUSH: {
                if(emu->stack_size > STACK_MAX){
                    return ERR_OVERFLOW;
                }
                emu->stack[emu->stack_size++] = emu->program[emu->program_ip].operand;
                emu->program_ip++;
            } break;
            case INST_PLUS: {
                if(emu->stack_size < 2){
                    return ERR_UNDERFLOW;
                }
                emu->stack[emu->stack_size - 2] = emu->stack[emu->stack_size - 1] + emu->stack[emu->stack_size - 2];
                emu->stack_size--;
                emu->program_ip++;
            } break;
            case INST_HALT: {
                emu->halted = 1;
                emu->program_ip++;
            } break;
            default: {
                printf("inst %s not yet implemented\n", inst_type_as_cstr(emu->program[emu->program_ip].type));
                exit(1);
            }
        }
    }
    return ERR_OK;
}