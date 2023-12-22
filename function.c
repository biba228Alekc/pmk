#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h>
#include "function.h"


#define SIZE 4

void generateRandomNumber(int length, int* numbers) {
    srand(time(NULL));
    // ���������� ��������� ����� �� 1 �� 9 ��� ������ �����
    numbers[0] = rand() % 9 + 1;

    // ���������� ��������� ����� ��������� �������
    for (int i = 1; i < length; i++) {
        numbers[i] = rand() % 10;
    }
}

void countBullsAndCows(int* numbers, int* array, int* bulls, int* cows) {
    int i, j;

    *bulls = 0;
    *cows = 0;

    for (i = 0; i < SIZE; i++) {
        if (numbers[i] == array[i]) {
            (*bulls)++;
        }
        else {
            for (j = 0; j < SIZE; j++) {
                if (numbers[i] == array[j]) {
                    (*cows)++;
                    break;
                }
            }
        }
    }
}