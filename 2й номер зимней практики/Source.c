#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include "matrixxxxxxxxxxx.h"

#pragma warning (disable: 4996)


int main() {
    setlocale(LC_ALL, "Rus");
    int size;
    printf("������� ������ �������: ");
    scanf("%d", &size);

    double** coefficients = (double**)malloc(size * sizeof(double*));
    double* constants = Array(size);

    printf("������� ������������ �������:\n");
    for (int i = 0; i < size; i++) {
        coefficients[i] = Array(size);
        for (int j = 0; j < size; j++) {
            printf("����������� a%d%d: ", i + 1, j + 1);
            scanf("%lf", &coefficients[i][j]);
        }
    }

    printf("������� ������� ��������� ������:\n");
    for (int i = 0; i < size; i++) {
        printf("b%d: ", i + 1);
        scanf("%lf", &constants[i]);
    }

    System(coefficients, constants, size);

    for (int i = 0; i < size; i++) {
        freeArray(coefficients[i]);
    }
    free(coefficients);
    freeArray(constants);

    return 0;
}