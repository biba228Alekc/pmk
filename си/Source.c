#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include"Header.h"

int main() 
{
    setlocale(LC_ALL, "Rus");
    int size;
    printf("������� ������ ������� �� ������� �������� ���������: ");
    scanf_s("%d", &size);
    //������� ��������� ������
    double* matrix = initializeArray1(size);
    //������� 
    double** matrixx = initializeMatrix(size);
    //������������ �������
    double determinant = determinantg(matrixx, size);
    //����� ������
    otvet(determinant, matrixx, size, matrix);
    return 1;
}
