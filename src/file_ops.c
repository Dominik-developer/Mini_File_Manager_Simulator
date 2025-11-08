#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <dirent.h>
#include "../include/menu.h"
#include "../include/file_ops.h"


void createFile(const char *filename) {

    FILE *pFile = fopen(filename, "r");

    if(pFile) {
        printf("File already exists: %s\n", filename);
        fclose(pFile);
        return;
    }
    pFile = fopen(filename, "w");
    if (!pFile) {
        printf("Error creating file: %s\n", filename);
        return;
    }

    fclose(pFile);
    printf("File created successfully: %s\n", filename);
}


void readFile(const char *filename) {

    FILE *pFile = fopen(filename, "r");

    if(!pFile){
        printf("File %s doesn't exist.\n", filename);
        return;
    }

    char line[256];
    while(fgets(line, sizeof(line), pFile)) {
        printf("%s", line); // prints line after line 
    }
    fclose(pFile);
    printf("\n--- End of file ---\n");
}


void deleteFile(const char *filename) {

    FILE *pFile = fopen(filename, "r"); 
    
    if(!pFile){
        printf("File %s doesn't exist.\n", filename);
        return;
    }

    fclose(pFile);
    
    printf("Are you sure you want to delete '%s'? (y/n): ", filename);
    char answer;
    scanf(" %c", &answer);

    if(answer != 'y' && answer != 'Y') {
        printf("Cancelled.\n");
        return;
    }
    
    if(remove(filename) == 0) {
            printf("File deleted successfully: %s\n", filename);
    } else {
        printf("Error deleting file: %s\n", filename);
    }
}


void listFiles(void) {

    DIR *pDir = opendir(".");

    if (!pDir) {
        printf("Error: could not open current directory.\n");
        return;
    }

    struct dirent *entry;   // represent every file/folder in dir
                            // pointer to the next entry in the directory during iteration

    int fileCount = 0;

    printf("Files in current directory:\n");
    while((entry = readdir(pDir)) != NULL) {    // assign pDir to entry and check if it's not null
                                                // fetch next entry until end of directory

        if(entry->d_type == DT_REG) {   //dt_reg normal file, dt_dir folders
                                        // DT_REG = regular file (skip directories and other types)
                                        
            printf("  %s\n", entry->d_name);    // prints dir name of entry struct
                                                // print the file name
            fileCount++;
        }
    }

    closedir(pDir);

    printf("Total files: %d\n", fileCount);
}


//EOF