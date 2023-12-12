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

// Recursive Binary Search. Takes array pointer, start/end index, and a search key
int bSearch(int *arrPtr, int start, int end, int key){
    // Makes sure the list isn't all checked by comparing start and end
    if (start != end){
        // Get midpoint
        int mid = (start + end) / 2;
        // If midpoint is too large call again with left side of list
        if (*(arrPtr + mid) > key){
            return bSearch(arrPtr, start, mid - 1, key);
        // If too small call again with right side of list
        } else if (*(arrPtr + mid) < key){
            return bSearch(arrPtr, mid+1, end, key);
        }
        // If not too small and not too large, must be the key. Return the location
        else{
            return mid;
        }
    // If list is all checked ensure the key is not located and return -1 to show it failed to locate key
    } else{
        if (*(arrPtr + start) == key){
            return start;
        } else{
            return -1;
        }
    }
}

int main(){
    // Defines length of array
    int arr[100000] = { };
    int arrLen = sizeof(arr)/sizeof(int);
    int *arrPtr = arr;
    // Fills array with random elements
    makeRandom(arrPtr, arrLen);
    // Tells what value to search for
    int key = 10000000;
    // Begins timer
    auto start = chrono::high_resolution_clock::now();
    ios_base::sync_with_stdio(false);
    // Searches
    int loc = bSearch(arrPtr, 0, arrLen-1, key);
    // Stops timer and runs some calculations
    auto end = chrono::high_resolution_clock::now();
    double time_taken = chrono::duration_cast<chrono::nanoseconds>(end - start).count();
    time_taken *= 1e-9;
    // Tells where the key was found
    if (loc >= 0){
        printf("The provided key can be found at index %d.\n", loc);
    } else{
        printf("The provided key was not found.\n");
    }
    // Prints the time taken
    printf("\n%f", time_taken);
    return 0;
}