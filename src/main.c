#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <dirent.h>
#include "../include/file_ops.h"

void processCommand(char *tokens[], int tokenCount);

int main() {

    bool isRunning = true;
    char command[100];

    loadAllFromDisk();

    while(isRunning) {

        printf("FileManager: $ ");

        if(fgets(command, sizeof(command), stdin) == NULL) {
            continue;
        }

        // removing enter character
        command[strcspn(command, "\n")] = '\0';

        // checking if command is empty
        if(strlen(command) == 0) {
            continue;
        }

        int maxTokens = 10; // max 10 words per command
        char *tokens[maxTokens]; // max 10 words; table of pointers
        int tokenCount = 0; // words in command counter

        char *token = strtok(command, " ");

        while(token != NULL && tokenCount < maxTokens) {
            tokens[tokenCount++] = token; // takes token and puts in in tokens table, tokenCount++ makes sure it next slot every time
            token = strtok(NULL, " ");
        }

        processCommand(tokens, tokenCount);

    }
    return 0;
}

// Additiona functions


void processCommand(char *tokens[], int tokenCount) {
// *tokens[] is the same as **tokens, both are correct way to show table of pointers
// *tokens[] is table of string pointers

    if(tokenCount == 0) return;

    if(strcmp(tokens[0], "exit") == 0) {
        saveAllToDisk();
        printf("Exiting File Manager...\n");
        exit(0);
    }
    else if(strcmp(tokens[0], "help") == 0) {
        printf("\n");
        printf("Available commands:\n");
        printf(" create <filename>\n");
        printf(" write <filename>\n");
        printf(" read <filename>\n");
        printf(" delete <filename>\n");
        printf(" list\n");
        printf(" exit\n");
        printf("\n");
    }
    else if(strcmp(tokens[0], "create") == 0) {
        if(tokenCount < 2) {
            printf("Usage: create <filename>\n");
        } else {
            createFile(tokens[1]);
        }
    }
    else if(strcmp(tokens[0], "write") == 0) {
        if(tokenCount < 3) {
            printf("Usage: write <filename> <text>\n");
        } else {

            // join all tokens from 2 to the end into one string
            char buffer[512] = "";
            for(int i = 2; i < tokenCount; i++) {
                strcat(buffer, tokens[i]);
                if(i < tokenCount - 1) strcat(buffer, " "); // add space between words
            }
            writeFile(tokens[1], buffer);
        }
    }
    else if(strcmp(tokens[0], "read") == 0) {
        if(tokenCount < 2) {
            printf("Usage: read <filename>\n");
        } else {
            readFile(tokens[1]);
        }
    }
    else if(strcmp(tokens[0], "delete") == 0) {
        if(tokenCount < 2) {
            printf("Usage: delete <filename>\n");
        } else {
            deleteFile(tokens[1]);
        }
    }
    else if(strcmp(tokens[0], "list") == 0) {
        listFiles();
    }
    else {
        printf("Unknown command: %s\n", tokens[0]);
    }
}

// EOF