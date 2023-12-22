#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h>
#include "function.h"

#define SIZE 4

int main()
{

    setlocale(LC_ALL, "Rus");
    int length = SIZE;
    int numbers[SIZE];// ���������� �����
    int array[SIZE];// ������������� ������
    int attempts = 0;
    generateRandomNumber(length, numbers);

  /*  printf("��������������� �����: ");
    for (int i = 0; i < length; i++) {
        printf("%d", numbers[i]);
    }
    printf("\n");*/

    int bulls, cows;

    printf("����� ���������� � ���� '���� � ������'!\n");
    printf("������� ����:\n");
    printf("- ������������ ���������� �������������� ���.\n");
    printf("- ����� ������ ������� �� �������� ���������� '�����' � '�����'.\n");
    printf("- '���' �������� ��������� ��������� ����� �� ���������� �������.\n");
    printf("- '������' �������� ��������� ��������� �����, �� �� ������������ �������.\n");
    printf("- ���� ���� - ������� ��� �� ����� �� 0 �� 9.\n\n");

    do {
        printf("������� ���� �������: ");
        scanf_s("%1d%1d%1d%1d", &array[0], &array[1], &array[2], &array[3]);

        countBullsAndCows(numbers, array, &bulls, &cows);
        printf("���������: %d ���(�)(��) � %d ������(�).\n\n", bulls, cows);

        attempts++;
    } while (bulls != SIZE);

    printf("����������! �� ������� ����� ����� %d �������.\n", attempts);

    return 0;
}