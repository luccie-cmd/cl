#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "common.h"
#include "compiler.h"

char *shift(int *argc, char ***argv){
    if(*argc == 0) return NULL;
    char *result = **argv;
    *argv+=1;
    *argc-=1;
    return result;
}

void usage(FILE *stream){
    fprintf(stream, "casm version: %d.%d.%d\n", VERSION_MAJOR, VERSION_MINOR, VERSION_PATCH);
    fprintf(stream, "casm -i [FILE] -o [FILE]\n");
    fprintf(stream, "extras\n");
    fprintf(stream, "   -v          print the version\n");
    fprintf(stream, "   -h          print the version and this help\n");
}

int main(int argc, char **argv){
    const char* const program = shift(&argc, &argv);
    (void) program;
    if(argc == 0){
        usage(stderr);
        printf("No file provided\n");
        exit(1);
    }
    char *in_file = NULL;
    char *out_file = NULL;
    while(argc > 0){
        char *arg = shift(&argc, &argv);
        if(strcmp(arg, "-o") == 0){
            char *file = shift(&argc, &argv);
            if(file == NULL){
                printf("No file for argument %s\n", arg);
                exit(1);
            }
            out_file = file;
        } else if(strcmp(arg, "-i") == 0){
            char *file = shift(&argc, &argv);
            if(file == NULL){
                printf("No file for argument %s\n", arg);
                exit(1);
            }
            if(!check_extention(file, "casm")){
                fprintf(stderr, "Invalid file type cannot parse\n");
                exit(1);
            }
            in_file = file;
        } else if(strcmp(arg, "-h") == 0){
            usage(stdout);
            exit(0);
        } else if(strcmp(arg, "-v") == 0){
            fprintf(stdout, "casm version: %d.%d.%d\n", VERSION_MAJOR, VERSION_MINOR, VERSION_PATCH);
            exit(0);
        } else{
            usage(stderr);
            printf("No argument named: %s\n", arg);
            exit(1);
        }
    }
    Compiler cm = {0};
    compiler_load_program_from_file(&cm, in_file);
    if(out_file == NULL){
        compiler_write_to_file(&cm, "./a.cl");
    } else{
        compiler_write_to_file(&cm, out_file);
    }
}