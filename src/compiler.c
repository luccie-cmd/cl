#include "compiler.h"

void compiler_print_program(const Compiler *com){
    printf("program:\n");
    if(com->program_size == 0){
        printf("    [EMPTY]");
    }
    for(size_t i = 0; i < com->program_size; ++i){
        printf("    type = %s operand = %lld\n", inst_type_as_cstr(com->program[i].type), com->program[i].operand);
    }
}
void compiler_add_to_program(Compiler *com, Inst item){
    assert(com->program_size < PROGRAM_MAX);
    com->program[com->program_size++] = item;
}
void compiler_load_program_from_file(Compiler *com, const char* path){
    String content = string_slurp_file(path);
    String line = string_chopByDelim(&content, '\n');
    while(line.count > 0){
        String inst_name = string_chopByDelim(&line, ' ');
        String operand = string_chopByDelim(&line, ';');
        if(string_eq(inst_name, string_from_cstr(inst_type_as_cstr(INST_PUSH)))){
            compiler_add_to_program(com, make_inst_push(string_to_int(operand)));
        } else if(string_eq(inst_name, string_from_cstr(inst_type_as_cstr(INST_PLUS)))){
            compiler_add_to_program(com, make_inst_plus());
        } else if(string_eq(inst_name, string_from_cstr(inst_type_as_cstr(INST_HALT)))){
            compiler_add_to_program(com, make_inst_halt());
        } else{
            printf("No instruction named: %.*s\n", (int) inst_name.count, inst_name.data);
            exit(1);
        }
        line = string_chopByDelim(&content, '\n');
    }
}
void compiler_write_to_file(Compiler *com, const char *path){
    FILE *f = fopen(path, "wb");
    if(!f){
        printf("Cannot find %s no such file or directory\n", path);
        exit(1);
    }
    for(size_t i = 0; i < com->program_size; ++i){
        switch(com->program[i].type){
            case INST_PUSH: {
                int push = 0x00;
                Word operand = com->program[i].operand;
                fwrite(&push, 1, 1, f);
                fwrite(&operand, 1, 1, f);
            } break;
            case INST_PLUS: {
                int plus = 0x01;
                fwrite(&plus, 1, 1, f);
            } break;
            case INST_HALT: {
                int halt = 0x02;
                fwrite(&halt, 1, 1, f);
            } break;
            default: {
                printf("%s not yet handled\n", inst_type_as_cstr(com->program[i].type));
                exit(1);
            } break;
        }
    }
}