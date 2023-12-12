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
        *(arrPtr + i) = rand()%1000;
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

// Iterates through array and checks if element is equal to key. If so return the index and if not found return -1
int lSearch(int *arrPtr, int len, int key){
    for (size_t i = 0; i < len; i++){
        if (*(arrPtr + i) == key){
            return i;
        }
    }
    return -1;
}

int main(){
    // Defines length of array
    int arr[1] = { };
    int arrLen = sizeof(arr)/sizeof(int);
    int *arrPtr = arr;
    // Fills array with random elements
    makeRandom(arrPtr, arrLen);
    // Tells what value to search for
    int search = 100000000;
    // Begins timer
    auto start = chrono::high_resolution_clock::now();
    ios_base::sync_with_stdio(false);
    // Searches
    int loc = lSearch(arrPtr, sizeof(arr)/sizeof(int), search);
    // Stops timer and runs some calculations
    auto end = chrono::high_resolution_clock::now();
    double time_taken = chrono::duration_cast<chrono::nanoseconds>(end - start).count();
    time_taken *= 1e-9;
    // Tells where the key was found
    if (loc >= 0){
        printf("The location of the key is at %d.\n", loc);
    } else{
        printf("The key was not found.");
    }
    // Prints the time taken
    printf("\n%f", time_taken);
}