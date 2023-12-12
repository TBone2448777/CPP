#include <cstdio>
#include <stdlib.h>
#include <time.h>

int printArray(int *arrPtr, int arrLen){
    for (size_t i = 0; i < arrLen - 1; i++){
        printf("%d, ", *(arrPtr + i));
    }
    printf("%d\n", *(arrPtr + arrLen - 1));
    return 0;
}

int makeRandom(int *arrPtr, int len){
    srand(time(NULL));
    for(size_t i = 0; i < len; i++){
        *(arrPtr + i) = rand()%1000;
    }
    return 0;
}

int main(){
    int arr[1000] = { };
    int len = sizeof(arr)/sizeof(int);
    int *arrPtr = arr;
    makeRandom(arrPtr, len);
    printArray(arrPtr, len);
}