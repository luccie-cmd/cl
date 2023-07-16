#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "emulator.h"
#include "common.h"

void usage(FILE *stream){
    fprintf(stream, "cle version: %d.%d.%d\n", VERSION_MAJOR, VERSION_MINOR, VERSION_PATCH);
    fprintf(stream, "cle [FILE]\n");
    fprintf(stream, "extras\n");
    fprintf(stream, "   -h          print the version and this help\n");
    fprintf(stream, "   -v          print the version\n");
    fprintf(stream, "   -o [FILE]   dump the stack to the file\n");
}

char *shift(int *argc, char ***argv){
    if(*argc == 0) return NULL;
    char *result = **argv;
    *argv+=1;
    *argc-=1;
    return result;
}

int main(int argc, char **argv){
    const char* const program = shift(&argc, &argv);
    (void) program;
    if(argc == 0){
        usage(stderr);
        printf("No input file provided\n");
        exit(1);
    }
    // char *out_file = NULL;
    char *in_file = NULL;
    while(argc > 0){
        char *arg = shift(&argc, &argv);
        if(strcmp(arg, "-h") == 0){
            usage(stdout);
            exit(0);
        } else if(strcmp(arg, "-v") == 0){
            fprintf(stdout, "cle version: %d.%d.%d\n", VERSION_MAJOR, VERSION_MINOR, VERSION_PATCH);
            exit(0);
        } else if(strcmp(arg, "-o") == 0){
            fprintf(stderr, "cle output not implemented yet");
            exit(1);
        } else{
            in_file = arg;
        }
    }
    Emulator emu = {0};
    if(in_file == NULL){
        fprintf(stderr, "No file provided\n");
        exit(1);
    }
    if(!check_extention(in_file, "cl")){
        fprintf(stderr, "Invalid file type cannot parse it\n");
        exit(1);
    }
    emulator_load_program_from_file(&emu, in_file);
    emulator_execute_program(&emu);
    emulator_print_stack(&emu);
}