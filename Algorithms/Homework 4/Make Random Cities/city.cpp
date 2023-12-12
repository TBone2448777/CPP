#include <cstdio>
#include <stdlib.h>
#include <time.h>

char getLetter(int num){
    if (0 <= num && num < 26){
        char alphabet[] = {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'};
        return alphabet[num];
    }
    return '!';
}

int randInt(int low, int high){
    static bool seeded = false;
    if (!seeded) {
        srand(time(NULL));
        seeded = true;
    }
    return rand() % (high - low + 1) + low;
}

class City{
    public:
        City(int index){
            char letter = getLetter(index);
            int xCord = 0;
            int yCord = 0;
        }
};

int main(){
    
}