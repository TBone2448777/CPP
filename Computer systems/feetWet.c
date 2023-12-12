#include <stdio.h>
int find_min(int arr[], int len){
    int curr_min = arr[0];
    for (int i = 1; i < len; i++){
        if (curr_min > arr[i]) curr_min = arr[i];
    }
    return curr_min;
}

int find_min2(int* arr, int len){
    int curr_min = *arr;
    for (int i = 1; i < len+1; i++, arr++){
        if (curr_min > *arr) curr_min = *arr;
    }
    return curr_min;
}

int main(void){
    int test[5] = {1,4,2,3,5};
    int test2[6] = {0,5,-3,3,11,1};
    int test3[4] = {0,0,4,-1};

    printf("The minimum in test is: %d (should be 1)\n", find_min(test,5));
    printf("The minimum in test2 is: %d (should be -3)\n", find_min(test2,6));
    printf("The minimum int test3 is: %d (should be -1)\n", find_min(test3,4));

    printf("\nThis time with pointers!\n");

    printf("The minimum in test is: %d (should be 1)\n", find_min2(test,5));
    printf("The minimum in test2 is: %d (should be -3)\n", find_min2(test2,6));
    printf("The minimum int test3 is: %d (should be -1)\n", find_min2(test3,4));
    return 0;
}
