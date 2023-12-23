#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include "matrixxxxxxxxxxx.h"


#pragma warning (disable: 4996)



double* Array(int size) {
    double* array = (double*)malloc(size * sizeof(double));
    if (array == NULL) {
        printf("Ошибка выделения памяти\n");
        exit(1);
    }
    return array;
}

void freeArray(double* array) {
    free(array);
}

double findDeterminant(double** matrix, int size) {
    if (size == 1) {
        return matrix[0][0];
    }
    else {
        double det = 0.0;
        double** subMatrix = (double**)malloc((size - 1) * sizeof(double*));
        for (int i = 0; i < size - 1; i++) {
            subMatrix[i] = Array(size - 1);
        }
        for (int i = 0; i < size; i++) {
            int subI = 0;
            for (int j = 1; j < size; j++) {
                int subJ = 0;
                for (int k = 0; k < size; k++) {
                    if (k != i) {
                        subMatrix[subI][subJ] = matrix[j][k];
                        subJ++;
                    }
                }
                subI++;
            }
            double subDet = findDeterminant(subMatrix, size - 1);
            if (i % 2 == 0) {
                det += matrix[0][i] * subDet;
            }
            else {
                det -= matrix[0][i] * subDet;
            }
        }
        for (int i = 0; i < size - 1; i++) {
            freeArray(subMatrix[i]);
        }
        free(subMatrix);
        return det;
    }
}

void System(double** coefficients, double* constants, int size) {
    double determinant = findDeterminant(coefficients, size);
    if (determinant == 0) {
        printf("Система имеет бесконечное число решений или не имеет решений.\n");
        return;
    }

    double* solutions = Array(size);
    for (int i = 0; i < size; i++) {
        double** tempMatrix = (double**)malloc(size * sizeof(double*));
        for (int j = 0; j < size; j++) {
            tempMatrix[j] = Array(size);
            for (int k = 0; k < size; k++) {
                tempMatrix[j][k] = (k == i) ? constants[j] : coefficients[j][k];
            }
        }
        solutions[i] = findDeterminant(tempMatrix, size) / determinant;
        for (int j = 0; j < size; j++) {
            freeArray(tempMatrix[j]);
        }
        free(tempMatrix);
    }

    printf("Решение системы:\n");
    for (int i = 0; i < size; i++) {
        printf("x%d = %f\n", i + 1, solutions[i]);
    }

    freeArray(solutions);
}
