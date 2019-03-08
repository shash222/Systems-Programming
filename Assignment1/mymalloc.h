
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <ctype.h>
#define malloc(param) mymalloc(param, __FILE__, __LINE__)
#define free(param) myfree(param, __FILE__, __LINE__)

static char mem[4096];

void reserveMemory(char* ptr, size_t size);

void* mymalloc(size_t size, char* file, int line);

void myfree(char* ptr, char* file, int line);
