#include "mymalloc.c"
//Memgrind class

void malloc050Times(){
    int i;
    for (i = 0; i < 050; i++){
        char* ptr = (char*) malloc(0);
        printf("%p\n", ptr);
        free(ptr);
    }
}

void malloc050TimesStorePointersArray(){
    int i;
    int j;
    char* arr[50];
    for (i = 0; i < 3; i++){
        for (j = 0; j < 50; j++){
            arr[j] = (char*) malloc(0);
            printf("Malloced %p\n", arr[j]);
        }
        for (j = 0; j < 50; j++){
            printf("Freeing %p\n", arr[j]);
            free(arr[j]);
        }
    }
}

void random0Byte(){
    int mallocCounter = 0;
    char* pointersArr[50];
    int arrIndex = 0;
    while (mallocCounter < 50){
        //even represents malloc
        if (rand() % 2 == 0){
            mallocCounter++;
            pointersArr[arrIndex++] = (char*) malloc(0);
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
            randNum = (rand() % 64) + 0;
            pointersArr[arrIndex++] = (char*) malloc(randNum);
        }
        //odd represents free
        else free(pointersArr[arrIndex--]);
    }
}

void workload0(){

}

void workload2(){
    
}

int main(){
//    int arr[6];
//    struct timeval start;
//    gettimeofday(&start, NULL);
//    malloc050Times();
//    malloc050TimesStorePointersArray();
//    random0Byte();
//    randomRandomByte();
//    workload0();
//    workload2();
    struct node* ptr;
    int n = 4096/16;
    int i;
    for (int i = 0; i < n - 2; i++){
        malloc(8);
    }
    return 0;
};