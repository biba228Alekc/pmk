#pragma once

#include "functions.h"
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <locale.h>

#define DIGITS 4


void generateSecretNumber(int secret[])
{
    setlocale(LC_ALL, "Rus");
    srand(time(NULL));

    secret[0] = rand() % 9 + 1; // ���������� ������ ����� �� 1 �� 9

    for (int i = 1; i < DIGITS; i++) {
        int digit;
        do {
            digit = rand() % 10; // ���������� ��������� ����� �� 0 �� 9
        } while (!isValidDigit(secret, i, digit)); // ����������, ��� ����� ���������

        secret[i] = digit; // ���������� ��������������� �����
    }
}


int isValidDigit(int secret[], int index, int digit) {
    setlocale(LC_ALL, "Rus");
    for (int i = 0; i < index; i++) {
        if (secret[i] == digit) {
            return 0; // ����� ��� ������������ � �����
        }
    }
    return 1; // ��� ����� ���������
}


void calculateBullsAndCows(int secret[], int guess[], int* bulls, int* cows) {
    setlocale(LC_ALL, "Rus");
    *bulls = 0;
    *cows = 0;

    for (int i = 0; i < DIGITS; i++) {
        if (secret[i] == guess[i]) {
            (*bulls)++; // ���� ����� ��������� �� �������, ����������� ���������� �����
        }
        else {
            for (int j = 0; j < DIGITS; j++) {
                if (secret[i] == guess[j]) {
                    (*cows)++; // ����������� ���������� �����
                    break;
                }
            }
        }
    }
}