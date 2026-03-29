#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    time_t seed= time(NULL);
    srand(seed);
   
    int token = rand();

    printf("I generated this at timestamp %ld)\n", seed);
 
    for(int i = 0; i < 300; i++) {
        printf("Generated %d: %d\n", i + 1, rand());
    }
    if(token == 0) {
        int bias_count = 0;
        for(int i = 0; i < 300; i++) {
            if(rand() == 0) bias_count++;
        }   
        printf("Bias count: %d\n", bias_count);
    }

    return 0;
}