#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include"Header.h"

int main() 
{
    setlocale(LC_ALL, "Rus");
    int size;
    printf("Введите размер матрицы из системы линейных уравнений: ");
    scanf_s("%d", &size);
    //Матрица свободных членов
    double* matrix = initializeArray1(size);
    //Матрица 
    double** matrixx = initializeMatrix(size);
    //Определитель Матрицы
    double determinant = determinantg(matrixx, size);
    //Вывод ответа
    otvet(determinant, matrixx, size, matrix);
    return 1;
}
