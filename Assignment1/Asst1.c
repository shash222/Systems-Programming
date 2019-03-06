#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "mymalloc.h"
#define malloc(param) mymalloc(param);
#define free(param) myfree(param);

void malloc150Times(){
    int i;
    for (i = 0; i < 150; i++){
        char* ptr = (char*) malloc(1);
        printf("%p\n", ptr);
        free(ptr);
    }
}

void malloc150TimesStorePointersArray(){
    int i;
    int j;
    char* arr[50];
    for (i = 0; i < 3; i++){
        for (j = 0; j < 50; j++){
            arr[j] = (char*) malloc(1);
            printf("Malloced %p\n", arr[j]);
        }
        for (j = 0; j < 50; j++){
            printf("Freeing %p\n", arr[j]);
            free(arr[j]);
        }
    }
}

void random1Byte(){
    int mallocCounter = 0;
    char* pointersArr[50];
    int arrIndex = 0;
    while (mallocCounter < 50){
        //even represents malloc
        if (rand() % 2 == 0){
            mallocCounter++;
            pointersArr[arrIndex++] = (char*) malloc(1);
        }
        //odd represents free
        else if (arrIndex > 0) free(pointersArr[arrIndex--]);
    }
    while (arrIndex >= 0) free(pointersArr[arrIndex--]);
}

void randomRandomByte(){
    int mallocCounter = 0;
    char* pointersArr[50];
    int arrIndex = 0;
    int randNum;
    while (mallocCounter < 50){
        if (rand() % 2 == 0){
            mallocCounter++;
            randNum = (rand() % 64) + 1;
            pointersArr[arrIndex++] = (char*) malloc(randNum);
        }
        //odd represents free
        else free(pointersArr[arrIndex--]);
    }
}



int main(){
//    malloc150Times();
//    malloc150TimesStorePointersArray();
//    random1Byte();
//    randomRandomByte();
//    workload1();
//    workload2();
};