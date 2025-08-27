#include <stdio.h>

// Increment the pointer by 1 (moves to next integer in memory)
void thr1(void *arg) {
    int *id = (int*)arg;
    id++; // Move pointer to next integer position
    printf("id: %d\n", *id); // Print the integer at new location
}

// Decrement the pointer by 1 (moves to previous integer in memory)
void thr2(void *arg) {
    int *id = (int*)arg;
    id--; // Move pointer to previous integer position
    printf("ido: %d\n", *id); // Print the integer at new location
}

int main() {
    int n = 2000; // Loop limit
    int id = 10;  // Base integer variable

    for (int i = 0; i < n; i++) {
        if (i % 2 == 0) {
            thr1((void*)&id);
            printf("even: %d\n", id);
        } else {
            thr2((void*)&id);
            printf("odd: %d\n", id);
        }
    }

    printf("Final id: %d\n", id);
    return 0;
}

