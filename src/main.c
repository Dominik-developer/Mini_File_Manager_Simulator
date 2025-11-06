#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "../include/menu.h"
#include "../include/file_ops.h"

void processCommand(char *tokens[], int tokenCount);

int main() {

    bool isRunning = true;
    char command[100];

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

    if (tokenCount == 0) return;

    if (strcmp(tokens[0], "exit") == 0) {
        printf("Exiting File Manager...\n");
        exit(0);
    }
    else if (strcmp(tokens[0], "help") == 0) {
        printf("\n");
        printf("Available commands:\n");
        printf(" create <filename>\n");
        printf(" write <filename>\n");
        printf(" read <filename>\n");
        printf(" delete <filename>\n");
        printf(" list\n");
        printf(" save\n");
        printf(" load\n");
        printf(" exit\n");
        printf("\n");
    }
    else {
        printf("Unknown command: %s\n", tokens[0]);
    }
}