#include "mymalloc.h"

//mymalloc.c class
struct node{
    short dataSize;//number of blocks being referred to
    struct node* next;
};

static int firstCall = 1;
static struct node* head = (struct node*) mem;
static int memAvailable = 4096;
static int sizeOfStruct = sizeof(struct node);
// lastAddress points to the last address that can be reserved (with a data size of 0)
// Accounts for only enough space for meta data to fit
static char* lastAddress = &mem[4095] - sizeof(struct node);

//Pointers point to address of next metadata, not next free address
void* spaceAvailable(size_t size){
    int spaceAvailable;
    int spaceNeeded = memAvailable - (sizeOfStruct + size);
    if (spaceNeeded < 0){
        return NULL;
    }
    if (firstCall == 1) return mem;
    struct node* ptr = head;
    char* dataStartPtr;
    struct node* next = ptr -> next;

    //spaceNeeded refers to space needed to reserve
    spaceNeeded = size + sizeOfStruct;
//    printf("%p %p %p\n", ptr, next, lastAddress);

    //No metadata will fit after address stored in lastAddress variable
    while((char*) next <= lastAddress){
        dataStartPtr = (char*)(ptr + 1);
        //spaceAvailable refers to space available between current data and next metadata
        spaceAvailable = (char*) next - dataStartPtr;
 //       printf("%p %p %d\n", next, dataStartPtr, spaceAvailable);

        //returns current pointer address if there is sufficient space after it
        //new data will be stored after current pointer being returned
        if (spaceAvailable >= spaceNeeded) return ptr;
        ptr = next;
        next = next -> next;
    }
    return NULL;
}

void* mymalloc(size_t size, char* file, int line){
    struct node* prev;
    if ((prev = (struct node*) spaceAvailable(size)) == NULL){
        printf("Not enough memory available!\n");
        return NULL;
    }
    memAvailable -= (size + sizeOfStruct);
    struct node* ptr;
    struct node* temp;
    if (firstCall == 1){
        ptr = prev;
        firstCall--;
        ptr -> next = (struct node*) lastAddress;
    }
    else{
        temp = prev -> next;
        prev -> next = (struct node*) (((char*) ptr) + prev -> dataSize);
        ptr = prev -> next;
        ptr -> next = temp;
    }
    ptr -> dataSize = size;
    // returning ++ptr because ptr is address at beginning of metadata, but ++ptr is address at beginning of user data (after metadata)
    printf("%p\n", ptr);
    return ++ptr;
} 

void myfree(char* ptr, char* file, int line){
    printf("MyFree");
}




/*
//int value of 0 denotes last item for stored value

void reserveMemory(char* ptr, size_t size){
    int i;
//    for (i = 0; i < size; i++) ptr[i] = size - i;
    //i < size - 1 because if size is 4, only 3 will be marked with 'b', and last will be marked with 'l'
    for (i = 0; i < size - 1; i++) ptr[i] = 'b';
    ptr[i] = 'l'
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
    while (ptr[i] != 'b'){
        ptr[i] = 0;
        i++;
    }
    ptr[i] = 0;
//    printf("Memory was freed successfully\n");
}*/