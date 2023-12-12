#include <stdio.h>

/* sums two numbers */
int compute_sum(int x, int y) {
    return x + y;
}

/*multiplies two numbers*/
int compute_product(int x, int y) {
    return x * y;
}

/* Function to perform calculations on a and b and set the
   parameters to their results */
void  calculate(int a, int b, int *sum_result, int *product_result) {
    *sum_result = compute_sum(a, b);
    *product_result = compute_product(a, b);
}

int main(void) {

    int a = 3, b = 4;
    int sum, product;
    
    calculate(a, b, &sum, &product); //modify this line!
    printf("sum of %d and %d is %d \n", a, b, sum);
    printf("product of %d and %d is %d \n", a, b, product);    
    return 0;
}