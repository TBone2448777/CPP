#include <cstdio>
#include <stdlib.h>
#include <time.h>
#include <bits-stdc++.h>
#include <chrono>
using namespace std;

//  Add quantity len random numbers to array pointed to by arrPtr
int makeRandom(int *arrPtr, int len){
    srand(time(NULL));
    for(size_t i = 0; i < len; i++){
        arrPtr[i] = rand()%1000;
    }
    return 0;
}

// Add quantity len numbers to array pointed to by arrPtr. If ord is 'a' or 'd' make the order ascend or descend
int makeRandomOrder(char ord, int *arrPtr, int len){
    // Seed Random
    srand(time(NULL));
    // Track is used to ensure increasing or decreasing
    int track;
    if (ord == 'a'){
        // If ascend start track low and add up to 5 at a time to it
        track = 0;
        for(size_t i = 0; i < len; i++){
            track += rand()%5;
            arrPtr[i] = track;
        }
    } else if (ord == 'd'){
        // If descend start track high and remove up to 5 at a time from it
        track = 10000;
        for(size_t i = 0; i < len; i++){
            track -= rand()%5;
            arrPtr[i] = track;
        }
    }
    return 0;
}

// Bubble Sort
int bubbleSort(int *arrPtr, size_t len){
    // Iterate through this len times
    for (size_t i=0; i < len; i++){
        // Go through all adjacent pairs of the array and swap if the left side is larger than the right
        for (size_t j=0; j < len-1; j++){
            if (*(arrPtr + j) > *(arrPtr + j + 1)){
                int temp = *(arrPtr + j);
                *(arrPtr + j) = *(arrPtr + j + 1);
                *(arrPtr + j + 1) = temp;
            }
        }
    }
    return 0;
}

// Prints array. Iterates through elements and prints each one followed by a comma
int printArray(int *arrPtr, int arrLen){
    for (size_t i = 0; i < arrLen - 1; i++){
        printf("%d, ", *(arrPtr + i));
    }
    printf("%d\n", *(arrPtr + arrLen - 1));
    return 0;
}

int main(){
    // Defines length of array
    int arr[1] = { };
    int arrLen = sizeof(arr)/sizeof(int);
    int *arrPtr = arr;
    // Fills array with random elements
    makeRandom(arrPtr, arrLen);
    // Begins timer
    auto start = chrono::high_resolution_clock::now();
    ios_base::sync_with_stdio(false);
    // Sorts
    bubbleSort(arrPtr, arrLen);
    // Stops timer and runs some calculations
    auto end = chrono::high_resolution_clock::now();
    double time_taken = chrono::duration_cast<chrono::nanoseconds>(end - start).count();
    time_taken *= 1e-9; 
    // Prints the time taken
    printf("%f", time_taken);
    return 0;
}