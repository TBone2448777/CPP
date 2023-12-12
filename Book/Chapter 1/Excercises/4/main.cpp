#include <cstdio>

int sum(int a, int b){
    return a + b;
}

int main(){
    int a = 5;
    int b = 10;
    printf("The sum of %d and %d is %d.\n", a, b, sum(a, b));
}