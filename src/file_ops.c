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

    bool found = false;

    for(int i = 0; i < fileCount; i++) {
        if(strcmp(files[i]->name, filename) == 0) {

            //found it
            found = true;

            // free space/memory from old content
            free(files[i]->content);

            // +1 beceuse \0 char at the end
            files[i]->content = malloc(strlen(text) + 1);

            // copy text safely
            strcpy(files[i]->content, text);
            
            printf("Content written to file: %s\n", filename);
            return;
        }
    }
    if (!found) {
        printf("File doesn't exist: %s\n", filename);
    } 
}

void readFile(const char *filename) {

    bool found = false;

    for(int i = 0; i < fileCount; i++) {
        if(strcmp(files[i]->name, filename) == 0) {

            //found it
            found = true;

            printf("=== %s ===\n", files[i]->name);

            if(files[i]->content && strlen(files[i]->content) > 0) { // strlen() return lenght of text
                printf("%s\n", files[i]->content);
            }
            else {
                printf("(empty file)\n");
            }

            printf("=============\n");
            return;
        }
    }
    if (!found) {
        printf("File doesn't exist: %s\n", filename);
    }
}

void deleteFile(const char *filename) {

    bool found = false;

    for(int i = 0; i < fileCount; i++) {
        if(strcmp(files[i]->name, filename) == 0) {
            
            //found it
            found = true;

            // free memory of the deleted file
            free(files[i]->name);
            free(files[i]->content);
            free(files[i]);

            //move all files to cover for deleted file; fixing dangling pointer problem
            //  Shift remaining elements left to fill the gap
            for(int j = i; j < fileCount - 1; j++) {
                files[j] = files[j+1];
            }
            // j=1 -> files[1] = files[2]

            // update file count for new count
            fileCount--;

            // shrink the dynamic array to free unused memory
            files = realloc(files, sizeof(File*) * fileCount);

            // if there are 0 elemnets/files free up all the memory
            if(fileCount == 0) {
                free(files);
                files = NULL;
            }

            printf("Deleted file: %s\n", filename);
            return;
        }
    }
    if (!found) {
        printf("File doesn't exist: %s\n", filename);
    }
}

void listFiles(void) {

    if(fileCount == 0) {
        printf("No files in memory.\n");
        return;
    }

    printf("Files in memory:\n");
    for(int i =0; i <fileCount; i++) {
        printf("  %d. %s\n", i + 1, files[i]->name);
    }

    printf("Total files: %d\n", fileCount);
}

// disk operations
void saveAllToDisk(void) {

}

void loadAllFromDisk(void) {

}


//EOF