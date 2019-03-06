#include <stdio.h>
#include <stdlib.h>

//int value of 0 denotes last item for stored value
static char mem[4096];

void reserveMemory(char* ptr, size_t size){
    int i;
    for (i = 0; i < size; i++) ptr[i] = size - i;
}

void printReserved(){
    int i;
    for (i = 0; i < 4096; i++){
        printf("%d: %d |", i, mem[i]);
    }
    printf("\n");
}

void* mymalloc(size_t size){
//    printf("Address from mymalloc: %p\n", &mem);
    int i;
    int max = 0;
    int consecutiveFree = 0;
     for (i = 0; i < 4096; i++){
        consecutiveFree = (mem[i] == 0) ? (consecutiveFree + 1) : 0;
        if (consecutiveFree > max) max = consecutiveFree;
        if (consecutiveFree == size){
            reserveMemory(&mem[i - consecutiveFree + 1], size);
//            printReserved();
//            printf("Allocated %d bytes\nMemory remaining %d\n", size, 4096 - size);
            return &mem[i - consecutiveFree + 1];
        }
    }
    printf("Cannot allocate enough memory. \nMax size available: %d\nAmount Needed: %d\n", max, size);
    return NULL;
}

void myfree(char* ptr){
    if (*ptr == 0){
        printf("Pointer points to null\n");
        return;
    }
    int i = 0;
    while (ptr[i] != 1){
        ptr[i] = 0;
        i++;
    }
    ptr[i] = 0;
//    printf("Memory was freed successfully\n");
}