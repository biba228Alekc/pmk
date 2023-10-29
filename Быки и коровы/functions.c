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

    secret[0] = rand() % 9 + 1; // Генерируем первую цифру от 1 до 9

    for (int i = 1; i < DIGITS; i++) {
        int digit;
        do {
            digit = rand() % 10; // Генерируем остальные цифры от 0 до 9
        } while (!isValidDigit(secret, i, digit)); // Убеждаемся, что цифры уникальны

        secret[i] = digit; // Записываем сгенерированную цифру
    }
}


int isValidDigit(int secret[], int index, int digit) {
    setlocale(LC_ALL, "Rus");
    for (int i = 0; i < index; i++) {
        if (secret[i] == digit) {
            return 0; // Цифра уже присутствует в числе
        }
    }
    return 1; // Все цифры уникальны
}


void calculateBullsAndCows(int secret[], int guess[], int* bulls, int* cows) {
    setlocale(LC_ALL, "Rus");
    *bulls = 0;
    *cows = 0;

    for (int i = 0; i < DIGITS; i++) {
        if (secret[i] == guess[i]) {
            (*bulls)++; // Если цифра совпадает по позиции, увеличиваем количество быков
        }
        else {
            for (int j = 0; j < DIGITS; j++) {
                if (secret[i] == guess[j]) {
                    (*cows)++; // Увеличиваем количество коров
                    break;
                }
            }
        }
    }
}