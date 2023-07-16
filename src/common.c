#include "common.h"
#define STRING_IMPLEMENTATION
#include "mystring.h"

uint8_t *slurp_file_bin(const char* path){
    FILE *f = fopen(path, "rb");
    if(f == NULL){
        printf("Failed to open %s\n", path);
        return NULL;
    }

    fseek(f, 0, SEEK_END);
    long size = ftell(f);
    fseek(f, 0, SEEK_SET);

    uint8_t* buffer = (uint8_t*)malloc(size);
    fread(buffer, 1, size, f);
    return buffer;
}

char *err_as_cstr(Err err){
    switch(err){
        case ERR_OK:           return "ERR_OK";           break;
        case ERR_OVERFLOW:     return "ERR_OVERFLOW";     break;
        case ERR_UNDERFLOW:    return "ERR_UNDERFLOW";    break;
        case ERR_ILLEGAL_INST: return "ERR_ILLEGAL_INST"; break;
        case ERR_ILLEGAL_INST_ACCESS: return "ERR_ILLEGAL_INST_ACCESS"; break;
        default:               return NULL;               break;
    }
    return NULL;
}

Inst make_inst_push(Word operand){
    return (Inst) {.type = INST_PUSH, .operand = operand};
}

Inst make_inst_plus(){
    return (Inst) {.type = INST_PLUS};
}

Inst make_inst_halt(){
    return (Inst) {.type = INST_HALT};
}

char *inst_type_as_cstr(Inst_Types type){
    switch(type){
        case INST_PUSH: return "push"; break;
        case INST_PLUS: return "plus"; break;
        case INST_HALT: return "halt"; break;
        default:        return NULL;   break;
    }
    return NULL;
}

int check_extention(char *path, char *extention){
    String spath = string_from_cstr(path);
    String sextention = string_from_cstr(extention);
    if(string_chopByDelim(&spath, '.').count == 0) string_chopByDelim(&spath, '.');
    return string_eq(spath, sextention);
}
