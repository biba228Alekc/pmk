#include <stdio.h>
#include <stdlib.h>
#include "matrixfunction.h"
#include <locale.h>

#pragma warning (disable: 4996)

void writeStringToFile(const char* str, const char* filename) {
    // Открываем файл для записи
    FILE* file = fopen(filename, "a+");

    if (file == NULL) {
        printf("Ошибка открытия файла.\n");
        return;
    }
    fclose(file);
}

// Функция для выделения памяти под матрицу размером n x n
double** createMatrix(int n) 
{
    double** matrix = (double**)malloc(n * sizeof(double*));
    for (int i = 0; i < n; i++) {
        matrix[i] = (double*)malloc(n * sizeof(double));
    }
    return matrix;
}


void write2MATRIXXToFile(double** matrix, int n, const char* filename) {
    FILE* file = fopen("matrixx.txt", "a");
    if (file == NULL) {
       printf("Ошибка открытия файла.");
        return;
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            fprintf(file, "%lf ", matrix[i][j]);
        }
        fprintf(file, "\n");
    }

    fclose(file);
}



// Функция для освобождения памяти, выделенной для матрицы
void freeMatrix(double** matrix, int n) {
    for (int i = 0; i < n; i++) {
        free(matrix[i]);
    }
    free(matrix);
}

// Функция для нахождения минора матрицы
void getMinor(double** src, double** dest, int her, int gaf, int n) {
    int i = 0, j = 0;
    for (int r = 0; r < n; r++) {
        for (int c = 0; c < n; c++) {
            if (r != her && c != gaf) {
                dest[i][j++] = src[r][c];
                if (j == n - 1) {
                    j = 0;
                    i++;
                }
            }
        }
    }
}

// Функция для нахождения определителя матрицы
double calcDeterminant(double** matrix, int n) {
    if (n == 1) {
        return matrix[0][0];
    }

    double det = 0;
    double** minor = createMatrix(n - 1);

    int sign = 1;
    for (int i = 0; i < n; i++) {
        getMinor(matrix, minor, 0, i, n);
        det += sign * matrix[0][i] * calcDeterminant(minor, n - 1);
        sign = -sign;
    }

    freeMatrix(minor, n - 1);

    return det;
}

// Функция для нахождения обратной матрицы
double** getInverseMatrix(double** matrix, int n) {
    double det = calcDeterminant(matrix, n);
    if (det == 0) {
        printf("Матрица вырожденная, обратной матрицы не существует.\n");
        return NULL;
    }

    double** inverseMatrix = createMatrix(n);
    double** minor = createMatrix(n - 1);

    int sign;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            sign = ((i + j) % 2 == 0) ? 1 : -1;
            getMinor(matrix, minor, i, j, n);
            inverseMatrix[j][i] = sign * calcDeterminant(minor, n - 1) / det;
        }
    }

    freeMatrix(minor, n - 1);

    return inverseMatrix;
}

// Функция для вывода матрицы на консоль
void printMatrix(double** matrix, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%.5f ", matrix[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

void Fstring(const char* str, const char* fileoname)
{
    FILE* fp = fopen("matrixx.txt", "a+");
    if (fp == NULL)
    {
        return 1;
    }
    for (int i = 0; i < str[i]; ++i)
        fputc(str[i], fp);
    fclose(fp);
}

void GGG(int n, double** matrix)
{
    printf("Введите элементы матрицы:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
           printf_s("Введите значение для %d-го элемента %d-й строки: ", j+1, i + 1);
            scanf("%lf", &matrix[i][j]);
        }
    }

}

void jjj(double** inverseMatrix, int n)
{
    if (inverseMatrix != NULL) 
    {
       printf("Обратная матрица:\n");
        printMatrix(inverseMatrix, n);
    }
}















