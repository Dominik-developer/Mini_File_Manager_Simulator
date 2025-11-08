#ifndef FILE_OPS_H
#define FILE_OPS_H


void createFile(const char *filename);
// we use const char *filename to pass pointer to chain of charst that can not be modified

void readFile(const char *filename);

void deleteFile(const char *filename);

void listFiles(void); // adding void to indicate no parameters


#endif