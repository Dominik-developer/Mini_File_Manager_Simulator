#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <dirent.h>
#include "../include/file_ops.h"


File **files = NULL; // initialize empty array of File pointers
int fileCount = 0; // start with zero files

// files operations
void createFile(const char *filename) {

    // Check if file already exists in memory
    for(int i = 0; i < fileCount; i++) {
        if(strcmp(files[i]->name, filename) == 0) {
            printf("File already exists: %s\n", filename);
            return;
        }
    }

    // Allocate memory for new File structure
    File *pNewFile = malloc(sizeof(File));

    if(!pNewFile) {
        printf("Memory allocation failed!\n");
        return;
    }

    // Allocate memory for file name and copy it
    pNewFile->name = strdup(filename);
    pNewFile->content = strdup("");

    // Expand the files array to hold the new file
    File **temp = realloc(files, sizeof(File*) * (fileCount + 1));
        // resize the dynamic array to hold one more File pointer
        // temp - temporary pointer to avoid losing original memory if realloc fails

    if(!temp) {
        printf("Memory allocation failed!\n");
        free(pNewFile->name);
        free(pNewFile->content);
        free(pNewFile);
        return;
    }

    files = temp; // assign the resized array back to files safely
        // commit resized array only if successful

    // Add newFile to array and increase fileCount
    files[fileCount] = pNewFile; // add new File pointer to the end of the array
    fileCount++; // increment the number of files in memory

    printf("File created: %s\n", filename);
}

void writeFile(const char *filename, const char *text) {

    FILE *pFile = fopen(filename, "w");

    if(!pFile){
        printf("File %s doesn't exist.\n", filename);
        printf("DO you wnat to create this file?");
        return;
    }
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


// disk operations
void saveAllToDisk(void) {

}

void loadAllFromDisk(void) {

}


//EOF