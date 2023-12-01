#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define ROWS 3
#define COLS 3
#define NUM_THREADS 3 // Number of threads to use

// Matrices A and B
int matrixA[ROWS][COLS] = {
    {1, 2, 3},
    {4, 5, 6},
    {7, 8, 9}
};

int matrixB[ROWS][COLS] = {
    {9, 8, 7},
    {6, 5, 4},
    {3, 2, 1}
};

// Result matrices for all operations
int matrixC[ROWS][COLS];
int matrixD[ROWS][COLS];
int matrixE[ROWS][COLS];
float matrixF[ROWS][COLS];

// Structure to pass data to each thread
typedef struct {
    int start_row;
    int end_row;
} ThreadData;

// Function to add matrices
void *matrixAddition(void *threadArg) {
    ThreadData *data = (ThreadData *)threadArg;
    for (int i = data->start_row; i < data->end_row; i++) {
        for (int j = 0; j < COLS; j++) {
            matrixC[i][j] = matrixA[i][j] + matrixB[i][j];
        }
    }
    pthread_exit(NULL);
}

// Function to subtract matrices
void *matrixSubtraction(void *threadArg) {
    ThreadData *data = (ThreadData *)threadArg;
    for (int i = data->start_row; i < data->end_row; i++) {
        for (int j = 0; j < COLS; j++) {
            matrixD[i][j] = matrixA[i][j] - matrixB[i][j];
        }
    }
    pthread_exit(NULL);
}

// Function to multiply matrices
void *matrixMultiplication(void *threadArg) {
    ThreadData *data = (ThreadData *)threadArg;
    for (int i = data->start_row; i < data->end_row; i++) {
        for (int j = 0; j < COLS; j++) {
            matrixE[i][j] = 0;
            for (int k = 0; k < COLS; k++) {
                matrixE[i][j] += matrixA[i][k] * matrixB[k][j];
            }
        }
    }
    pthread_exit(NULL);
}

// Function to divide matrices (element-wise)
void *matrixDivision(void *threadArg) {
    ThreadData *data = (ThreadData *)threadArg;
    for (int i = data->start_row; i < data->end_row; i++) {
        for (int j = 0; j < COLS; j++) {
            matrixF[i][j] = (float)matrixA[i][j] / matrixB[i][j];
        }
    }
    pthread_exit(NULL);
}

int main() {
    pthread_t threads[NUM_THREADS];
    ThreadData threadData[NUM_THREADS];

    // Create threads for addition
    int rowsPerThread = ROWS / NUM_THREADS;
    for (int i = 0; i < NUM_THREADS; i++) {
        threadData[i].start_row = i * rowsPerThread;
        threadData[i].end_row = (i + 1) * rowsPerThread;
        pthread_create(&threads[i], NULL, matrixAddition, (void *)&threadData[i]);
    }

    // Wait for addition threads to finish
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    // Create threads for subtraction
    for (int i = 0; i < NUM_THREADS; i++) {
        threadData[i].start_row = i * rowsPerThread;
        threadData[i].end_row = (i + 1) * rowsPerThread;
        pthread_create(&threads[i], NULL, matrixSubtraction, (void *)&threadData[i]);
    }

    // Wait for subtraction threads to finish
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    // Create threads for multiplication
    for (int i = 0; i < NUM_THREADS; i++) {
        threadData[i].start_row = i * rowsPerThread;
        threadData[i].end_row = (i + 1) * rowsPerThread;
        pthread_create(&threads[i], NULL, matrixMultiplication, (void *)&threadData[i]);
    }

    // Wait for multiplication threads to finish
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    // Create threads for division
    for (int i = 0; i < NUM_THREADS; i++) {
        threadData[i].start_row = i * rowsPerThread;
        threadData[i].end_row = (i + 1) * rowsPerThread;
        pthread_create(&threads[i], NULL, matrixDivision, (void *)&threadData[i]);
    }

    // Wait for division threads to finish
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    // Display the result matrices
    printf("Result Matrix C (Addition):\n");
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            printf("%d ", matrixC[i][j]);
        }
        printf("\n");
    }

    printf("\nResult Matrix D (Subtraction):\n");
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            printf("%d ", matrixD[i][j]);
        }
        printf("\n");
    }
    

    printf("\nResult Matrix E (Multiplication):\n");
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            printf("%d ", matrixE[i][j]);
        }
        printf("\n");
    }

    printf("\nResult Matrix F (Division):\n");
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            printf("%.2f ", matrixF[i][j]);
        }
        printf("\n");
    }

    return 0;
}