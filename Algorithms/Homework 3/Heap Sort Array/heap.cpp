#include <cstdio>
#include <stdlib.h>
#include <time.h>
#include <bits-stdc++.h>
#include <chrono>
#include <cmath>
using namespace std;

//  Add quantity len random numbers to array pointed to by arrPtr
int makeRandom(int *arrPtr, int len){
    srand(time(NULL));
    for(size_t i = 0; i < len; i++){
        *(arrPtr + i) = rand()%1000;
    }
    return 0;
}

void heapify(int *arr, int len, int curr){
    int largest = curr;
    int left = 2 * curr + 1;
    int right = 2 * curr + 2;
    if (left < len && arr[curr] < arr[left]){
        largest = left;
    }
    if (right < len && arr[largest] < arr[right]){
        largest = right;
    }
    if (largest != curr){
        int holder = arr[curr];
        arr[curr] = arr[largest];
        arr[largest] = holder;
        heapify(arr, len, largest);
    }
}

void printArray(int *arrPtr, int arrLen){
    for (size_t i = 0; i < arrLen - 1; i++){
        printf("%d, ", *(arrPtr + i));
    }
    printf("%d\n", *(arrPtr + arrLen - 1));
}

int heapSort(int *arr, int len){
    int obj = -1;
    for (int i = floor(len/2)-1; i > -1; i--){
        heapify(arr, len, i);
    }
    printArray(arr, len);
    for (size_t i = len-1; i > 0; i--){
        int holder = arr[i];
        arr[i] = arr[0];
        arr[0] = holder;
        heapify(arr, i, 0);
    }
    return obj;
}

int main(){
    // Defines length of array
    int kth = 5;
    int arr[100] = {};
    int arrLen = sizeof(arr)/sizeof(int);
    int *arrPtr = arr;
    // Fills array with random elements
    makeRandom(arrPtr, arrLen);
    // Print array before
    printArray(arrPtr, arrLen);
    // Begin heapsort
    int val = heapSort(arrPtr, arrLen);
    printf("The %dth smallest value is %d\n", kth, arr[kth-1]);
    // Print array after
    printArray(arrPtr, arrLen);
}