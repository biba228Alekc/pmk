#include <stdio.h>
#include <time.h>
#include <locale.h>


#define DIGITS 4


int main()
{
    setlocale(LC_ALL, "Rus");
    int secret[DIGITS]; // ���������� �����
    int guess[DIGITS]; // ������������� ������
    int bulls, cows;

    printf("����� ���������� � ���� ���� � ������!\n");
    printf("������� ����: ��������� ���������� ����� �� %d ��������������� ���� �� 1 �� 9,\n", DIGITS);
    printf("���� ������ - ������� ��� �����.\n");

    generateSecretNumber(secret); // ���������� ���������� �����

    do {
        printf("������� ���� �������������: ");
        for (int i = 0; i < DIGITS; i++) {
            scanf_s("%1d", &guess[i]); // ��������� �� ����� �����
        }

        calculateBullsAndCows(secret, guess, &bulls, &cows); // ��������� ���������� ����� � �����

        printf("����: %d, ������: %d\n", bulls, cows);

    } while (bulls != DIGITS); // ���� ������������, ���� �� ������� �����

    printf("����������! �� ������� �����.\n");

    return 0;
}