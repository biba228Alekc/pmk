#include <stdio.h>
#include <locale.h>
#include "function.h"



//��������, ��� ����� 36 ���������� 12 ������� ��� � �������
//������� � ��� ����� (1, 5, 7, 11, 13, 17, 19, 23, 25, 29, 31, 35), ������� 
// euler(36)=12.



int main()
{
    setlocale(LC_ALL, "Rus");
    int n;
    printf("������� ����� n: ");
    scanf_s("%d", &n);

    int phi = euler(n);
    printf("������� ������ ��� ����� %d: %d\n", n, phi);

    return 0;
}
