#ifndef FILE_OPS_H
#define FILE_OPS_H

typedef struct {

    char *name; // file name
    char *content; // file content

} File;

extern File **files; // pointer to dynamic array of File pointers
extern int fileCount; // number of files currently in memory


// memory functions
void createFile(const char *filename); // we use const char *filename to pass pointer to chain of charst that can not be modified
void writeFile(const char *filename, const char *text);
void readFile(const char *filename);
void deleteFile(const char *filename);
void listFiles(void); // adding void to indicate no parameters

//disk functions
void saveAllToDisk(void);
void loadAllFromDisk(void);
void clearMemory(void);

#endif