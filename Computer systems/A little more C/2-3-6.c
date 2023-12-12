#include <stdio.h>
int swap(char *a, char *b);

int main(void) {
    char alpha, beta;
    int ret;

    alpha = 'a';
    beta = 'b';
    
    ret = swap(&alpha, &beta);
    printf("alpha: %c beta: %c \n", alpha, beta);
    printf("The return value is: %d\n", ret);

    return 0;
}

/* swaps values pointed to by a and b. Returns 0 on success, 1 on error. 
 */
int swap(char *a, char *b) {
    if (*a && *b){
        char saver = *b;
        *b = *a;
        *a = saver;
        return 0;
    } else {
        return 1;
    }
}