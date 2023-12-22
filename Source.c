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
    int numbers[SIZE];// Загаданное число
    int array[SIZE];// Предположение игрока
    int attempts = 0;
    generateRandomNumber(length, numbers);

  /*  printf("Сгенерированное число: ");
    for (int i = 0; i < length; i++) {
        printf("%d", numbers[i]);
    }
    printf("\n");*/

    int bulls, cows;

    printf("Добро пожаловать в игру 'Быки и коровы'!\n");
    printf("Правила игры:\n");
    printf("- Предположите загаданный четырехзначный код.\n");
    printf("- После каждой попытки вы получите количество 'быков' и 'коров'.\n");
    printf("- 'Бык' означает правильно угаданную цифру на правильной позиции.\n");
    printf("- 'Корова' означает правильно угаданную цифру, но на неправильной позиции.\n");
    printf("- Цель игры - угадать код из чисел от 0 до 9.\n\n");

    do {
        printf("Введите вашу попытку: ");
        scanf_s("%1d%1d%1d%1d", &array[0], &array[1], &array[2], &array[3]);

        countBullsAndCows(numbers, array, &bulls, &cows);
        printf("Результат: %d бык(а)(ов) и %d корова(ы).\n\n", bulls, cows);

        attempts++;
    } while (bulls != SIZE);

    printf("Поздравляю! Вы угадали число после %d попыток.\n", attempts);

    return 0;
}