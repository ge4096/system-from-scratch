#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "assembler.h"

int main(int argc, char ** argv){
    if(argc != 3){
        printf("Usage: %s infile outfile\n", argv[0]);
        return 1;
    }

    FILE * in_file = fopen(argv[1], "r");
    if(in_file == NULL){
        printf("Could not open input file\n");
        return 1;
    }

    char * temp_output_filename = (char *)malloc(sizeof(char) *
                                                 (strlen(argv[2]) + 7));
    strcpy(temp_output_filename, argv[2]);
    strcat(temp_output_filename, "XXXXXX");
    mkstemp(temp_output_filename);
    FILE * out_file = fopen(temp_output_filename, "wb");
    if(out_file == NULL){
        printf("Could not open temp output file\n");
        return 1;
    }

    int assembler_success = assemble(in_file, out_file, argv[1]);

    fclose(in_file);
    fclose(out_file);

    if(assembler_success == 0){
        if(rename(temp_output_filename, argv[2]) != 0){
            printf("Could not write output file\n");
            return 1;
        }
    }
    else{
        remove(temp_output_filename);
    }
    free(temp_output_filename);

    return assembler_success;
}
