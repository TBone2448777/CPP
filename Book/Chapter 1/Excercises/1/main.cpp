#include <cstdio>

int absolute_value(int n){
    if (n > 0){
        return n;
    } else if (n < 0){
        return n*(-1);
    } else{
        return 0;
    }
}

int main(){
    int my_num = -1;
    printf("The absolute value of %d is %d.\n", my_num, absolute_value(my_num));
}