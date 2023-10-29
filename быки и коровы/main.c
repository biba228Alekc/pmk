#include <stdio.h>
#include <time.h>
#include <locale.h>


#define DIGITS 4


int main()
{
    setlocale(LC_ALL, "Rus");
    int secret[DIGITS]; // Загаданное число
    int guess[DIGITS]; // Предположение игрока
    int bulls, cows;

    printf("Добро пожаловать в игру Быки и Коровы!\n");
    printf("Правила игры: компьютер загадывает число из %d неповторяющихся цифр от 1 до 9,\n", DIGITS);
    printf("ваша задача - угадать это число.\n");

    generateSecretNumber(secret); // Генерируем загаданное число

    do {
        printf("Введите ваше предположение: ");
        for (int i = 0; i < DIGITS; i++) {
            scanf_s("%1d", &guess[i]); // Считываем по одной цифре
        }

        calculateBullsAndCows(secret, guess, &bulls, &cows); // Вычисляем количество быков и коров

        printf("Быки: %d, Коровы: %d\n", bulls, cows);

    } while (bulls != DIGITS); // Игра продолжается, пока не угадано число

    printf("Поздравляю! Вы угадали число.\n");

    return 0;
}