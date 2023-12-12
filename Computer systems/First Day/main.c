#include <stdio.h>
int main(){
    int arr[] = {0, 1, 2, 3, 4};
    for (size_t i = 0; i < sizeof(arr)/sizeof(int)-1; i++){
        printf("%d, ", arr[i]);
    }
    printf("%d", arr[sizeof(arr)/sizeof(int)-1]);
    return 0;
}