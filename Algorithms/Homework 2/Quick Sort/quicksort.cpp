#include <cstdio>
#include <stdlib.h>
#include <time.h>
#include <bits-stdc++.h>
#include <chrono>
using namespace std;

//  Add quantity len random numbers to array pointed to by arrPtr
void makeRandom(int *arrPtr, int len){
    srand(time(NULL));
    for(size_t i = 0; i < len; i++){
        arrPtr[i] = rand()%1000;
    }
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

// When passed an array and two indexes, switches the two indexes in the array
void swap(int *arrPtr, int p1, int p2){
    int temp = *(arrPtr + p1);
    *(arrPtr + p1) = *(arrPtr + p2);
    *(arrPtr + p2) = temp;
}

// Gets a random value between min and max
int random(int min, int max){
    srand(time(NULL));
    return rand()%(max-min+1)+min;
}

// Splits the array into two pieces
// Basically gets a random pivot and puts everything larger than it to the right of it, and everything less than it on the left of it
int inPlacePartition(int *S, int a, int b){
    // Gets a random number that would fall in the array
    int r = random(a, b);
    // Swap that random value with the last index
    swap(S, r, b);
    // The randomly chosen value is now the pivot and at the end of the array
    int pivot = S[b];
    // Define left and right. Left is leftmost index and right is rightmost
    int left = a;
    int right = b - 1;
    // While left and right are not on top of one another
    while (left <= right){
        // Iterate through the left side making sure nothing is larger than the pivot. If something is, stop
        while (left <= right && S[left] <= pivot){
            left = left + 1;
        }
        // Iterate through the right side making sure nothing is smaller than the pivot. If something is, stop
        while (right >= left && S[right] >= pivot){
            right = right-1;
        }
        // Now that both sides have reached a value outside of their rules, swap them so they can continue
        if (left < right){
            swap(S, left, right);
        }
    }
    // Return the pivot to the spot in the middle
    swap(S, left, b);
    return left;
}

// In place quick sort
int inPlaceQuickSort(int *S, int a, int b){
    // Makes sure the subarray input has values
    if (a >= b){
        return 0;
    }
    // Get array split into a larger than pivot and smaller than pivot sides
    int c = inPlacePartition(S, a, b);
    // Sort the left side stopping at previous pivot
    inPlaceQuickSort(S, a, c-1);
    // Sort the right side stopping at previous pivot
    inPlaceQuickSort(S, c+1, b);
    return 0;
    // Eventually after being passed through enough it will be fully sorted.
}

// Prints array. Iterates through elements and prints each one followed by a comma
void printArray(int *arrPtr, int arrLen){
    for (size_t i = 0; i < arrLen - 1; i++){
        printf("%d, ", *(arrPtr + i));
    }
    printf("%d\n", *(arrPtr + arrLen - 1));
}

int main(){
    // Defines length of array
    int arr[10000] = { };
    int arrLen = sizeof(arr)/sizeof(int);
    int *arrPtr = arr;
    // Fills array with random elements
    makeRandom(arrPtr, arrLen);
    // printArray(arrPtr, arrLen);
    // Begins timer
    auto start = chrono::high_resolution_clock::now();
    ios_base::sync_with_stdio(false);
    // Sorts
    inPlaceQuickSort(arr, 0, arrLen-1);
    // Stops timer and runs some calculations
    auto end = chrono::high_resolution_clock::now();
    double time_taken = chrono::duration_cast<chrono::nanoseconds>(end - start).count();
    time_taken *= 1e-9; 
    // Prints the time taken
    printf("%f\n", time_taken);
    // printArray(arrPtr, arrLen);
    return 0;
}