#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

// Global matrices
int **m1 = NULL;
int **m2 = NULL;
int **res = NULL;
int r1, c1, r2, c2;

// Thread function to compute one row of result matrix
void *fun(void *arg) {
    int row = *(int*)arg;  // get row index
    free(arg);             // free allocated memory

    for (int j = 0; j < c2; j++) {
        res[row][j] = 0;   // initialize before summation
        for (int k = 0; k < c1; k++) {
            res[row][j] += m1[row][k] * m2[k][j];
        }
    }
    return NULL;
}

int main() {
    // Input first matrix
    printf("Enter the row: ");
    scanf("%d", &r1);
    printf("Enter the column: ");
    scanf("%d", &c1);

    m1 = (int**)malloc(r1 * sizeof(int*));
    printf("Enter the elements of m1 matrix: ");
    for (int i = 0; i < r1; i++) {
        m1[i] = (int*)malloc(c1 * sizeof(int));
        for (int j = 0; j < c1; j++) {
            scanf("%d", &m1[i][j]);
        }
    }

    // Input second matrix
    printf("Enter the row: ");
    scanf("%d", &r2);
    printf("Enter the column: ");
    scanf("%d", &c2);

    // Check for valid multiplication
    if (c1 != r2) {
        printf("Matrix multiplication not possible!\n");
        return -1;
    }

    m2 = (int**)malloc(r2 * sizeof(int*));
    printf("Enter the elements of m2 matrix: ");
    for (int i = 0; i < r2; i++) {
        m2[i] = (int*)malloc(c2 * sizeof(int));
        for (int j = 0; j < c2; j++) {
            scanf("%d", &m2[i][j]);
        }
    }

    // Allocate result matrix
    res = (int**)malloc(r1 * sizeof(int*));
    for (int i = 0; i < r1; i++) {
        res[i] = (int*)malloc(c2 * sizeof(int));
    }

    // Create one thread per row
    pthread_t thread[r1];
    for (int i = 0; i < r1; i++) {
        int *row = malloc(sizeof(int)); // allocate separate memory
        *row = i;
        pthread_create(&thread[i], NULL, fun, row);
    }

    // Join threads
    for (int i = 0; i < r1; i++) {
        pthread_join(thread[i], NULL);
    }

    // Print result matrix
    printf("The resultant Matrix:\n");
    for (int i = 0; i < r1; i++) {
        for (int j = 0; j < c2; j++) {
            printf("%d ", res[i][j]);
        }
        printf("\n");
    }

    // Free allocated memory
    for (int i = 0; i < r1; i++) free(m1[i]);
    for (int i = 0; i < r2; i++) free(m2[i]);
    for (int i = 0; i < r1; i++) free(res[i]);
    free(m1); free(m2); free(res);

    return 0;
}

