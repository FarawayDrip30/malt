#include <stdio.h>
#include <string.h>

void load_string_from_file(char* output, char* path, int string_size){
    FILE *fptr;
    fptr = fopen(path, "r");
    char short_string[100];
    char file_string[string_size];
    
    // Clear file_string, else last file's read is kept in memory
    strncpy(file_string, "", sizeof(file_string));
    
    while(fgets(short_string, 100, fptr)){
        sprintf(file_string, "%s%s", file_string, short_string);
    }
    fclose(fptr);

    strncpy(output, file_string, strlen(file_string)+1);
}