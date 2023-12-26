#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include"Header.h"

//������� ��� ��������� ������ ��� ���������� ������
double* createDynamicArray(int size)
{
    double* array = (double*)malloc(size * sizeof(double));
    return array;
}

// ������� ��� ��������� ������ ��� ������� �������� size x size
double** create1Matrix(int size)
{
    double** matrix = (double**)malloc(size * sizeof(double*));
    for (int i = 0; i < size; i++) {
        matrix[i] = (double*)malloc(size * sizeof(double));
    }
    return matrix;
}
//������� �������������� ������ ��������� ������������
double** initializeMatrix(int size)
{
        double** matrixx = create1Matrix(size);
        for (int i = 0; i < size; i++)
        {
            for (int j = 0; j < size; j++)
            {
                // ��� ��� ��� ������������� ��������� �������
                // ��������, ����� ������������ ������� scanf ��� ����� ��������:
                printf("������� �������� �������� ������� �������(������� ���������) [%d][%d]: ", i+1, j+1);
                scanf_s("%lf", &matrixx[i][j]);
            }
        }
        return matrixx;
}
//������� �������������� ������ ���������� ������������
double* initializeArray1(int size)
{
    double* matrix = createDynamicArray(size);
    for (int i = 0; i < size; i++)
    {
        // ��� ��� ��� ������������� ��������� �������
        // ��������, ����� ������������ ������� scanf ��� ����� ��������:
        printf("������� �������� �������� ��������� ������ [%d]: ", i+1);
        scanf_s("%lf", &matrix[i]);
    }
    return matrix;
}

//������� ��� �������� ������������
double determinantg(double** matrix, int size) {
    if (size == 1) {
        return matrix[0][0];
    }
    else if (size == 2) {
        return (matrix[0][0] * matrix[1][1]) - (matrix[0][1] * matrix[1][0]);
    }
    else {
        double det = 0;
        int sign = 1;
        for (int i = 0; i < size; i++) {
            // ������� ���������� ��� ������ ������ � �������� �������
            double** submatrix = (double**)malloc((size - 1) * sizeof(double*));
            for (int j = 0; j < size - 1; j++) {
                submatrix[j] = (double*)malloc((size - 1) * sizeof(double));
            }
            for (int j = 1; j < size; j++) {
                int k = 0;
                for (int l = 0; l < size; l++) {
                    if (l != i) {
                        submatrix[j - 1][k] = matrix[j][l];
                        k++;
                    }
                }
            }
            det += sign * matrix[0][i] * determinantg(submatrix, size - 1);

            // ����������� ������, ���������� ��� ����������
            for (int j = 0; j < size - 1; j++) {
                free(submatrix[j]);
            }
            free(submatrix);

            sign = -sign;
        }
        return det;
    }
}

int createModifiedArray(double** inputArray, double* oneDimensionalArray, int size, double determ)
{ 

    // ������� ����� ��������� ������
    double** modifiedArray = create1Matrix(size);
    // ��������� ����� ������ ����������
    int size2=0;
    for (int g = 0; g < size; g++)
    {
        for (int i = 0; i < size; i++)
        {
            for (int j = 0; j < size; j++)
            {

                if (j == size2) {
                    // �������� ��������� ������� �� ������� �� ����������� �������
                    modifiedArray[i][j] = oneDimensionalArray[i];

                }
                else {
                    // ��������� ��������� ������� ���������� �� ���������� �������
                    modifiedArray[i][j] = inputArray[i][j];
                }
            }
        }
        //��������� ������
        double det = determinantg(modifiedArray, size);
        double x = det / determ;
        printf("%lf :����� x%d\n", x, size2+1);
        size2++;
    }
    return 1;
}

void otvet(double determinant, double** matrixx, int size, double* matrix)
{
    printf("������������ ������� %lf\n", determinant);
    if (determinant != 0)
    {
        int x = createModifiedArray(matrixx, matrix, size, determinant);
        return 1;
    }
    else
    {
        printf("������� �� ����� �������, �� ������������ ����� 0");
    }
}


