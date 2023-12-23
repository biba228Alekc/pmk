#include <stdio.h>
#include <stdlib.h>
#include "matrixfunction.h"
#include <locale.h>

#pragma warning (disable: 4996)

int main() {
    setlocale(LC_ALL, "Rus");

    int n;
    printf("Введите размерность матрицы: ");
    scanf_s("%d", &n);

    double** matrix = createMatrix(n);

    GGG(n, matrix);

    double** inverseMatrix = getInverseMatrix(matrix, n);

    jjj( inverseMatrix, n);

    char str1[] = "Исходная квадратная матрица размера n.\n";
    char str2[] = "Обратная матрица к исходной размера n\n";
    FILE* f;
    f = fopen("matrixx.txt", "w");
    fprintf(f, "%s", "Исходная квадратная матрица размера n.\n");
    fclose(f);
  
   
    write2MATRIXXToFile(matrix, n, "matrixx.txt");

  
    FILE* fr;
    fr = fopen("matrixx.txt", "a+");
    fprintf(fr, "%s", "Обратная матрица к исходной размера n.\n");
    fclose(fr);
    write2MATRIXXToFile(inverseMatrix, n, "matrixx.txt");

    freeMatrix(matrix, n);

    freeMatrix(inverseMatrix, n);

    return 0;
}
