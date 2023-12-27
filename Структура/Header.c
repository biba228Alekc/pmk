#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
#include <time.h>
#include "Header.h"

#pragma warning(disable : 4996)


#define MAX_WORKERS 100
//Функция читает файл и записывает информацию из нее в структуру
void readWorkersFromFile(struct Storage* storage, const char* fileName) {
    FILE* file = fopen(fileName, "r");
    if (file == NULL) {
        printf("Ошибка открытия файла: %s\n", fileName);
        return;
    }

    while (!feof(file) && storage->count < MAX_WORKERS) {
        fscanf(file, "%s %s %d %d %d %d %f",
            storage->workers[storage->count].surname,
            storage->workers[storage->count].position,
            &storage->workers[storage->count].contractDate.day,
            &storage->workers[storage->count].contractDate.month,
            &storage->workers[storage->count].contractDate.year,
            &storage->workers[storage->count].contractDuration,
            &storage->workers[storage->count].salary);
        storage->count++;
    }

    fclose(file);
}

// Функция выводит на экран рабочих подходящих по условию
void printRecentWorkers(const struct Storage* storage) {
    struct Date currentDate;
    // Выставление текущей даты
    currentDate.day = 27;
    currentDate.month = 12;
    currentDate.year = 2023;

    printf("Вывод рабочих:\n");
    for (int i = 0; i < storage->count; i++) {
        struct Worker worker = storage->workers[i];
        struct Date date2 = { 27, 12, 2023 };
        struct Date date1 = { worker.contractDate.day, worker.contractDate.month, worker.contractDate.year };
        int dayCount1 = getDayCount(date1);
        int dayCount2 = getDayCount(date2);
        int daysDiff = dayCount2 - dayCount1;
            if (daysDiff < 365 && daysDiff>0)
            {
                printf("- Surname: %s\n", worker.surname);
                printf("  Position: %s\n", worker.position);
                printf("  Contract Date: %02d-%02d-%04d\n", worker.contractDate.day, worker.contractDate.month, worker.contractDate.year);
                printf("  Contract Duration: %d days\n", worker.contractDuration);
                printf("  Salary: %.2f\n", worker.salary);
            }
    }
}
//Функция проверки на весокосный год
int isLeapYear(int year) {
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}
// Функция считает количество дней в дате
int getDayCount(struct Date date) {
    // Количество дней в каждом месяце
    int daysInMonth[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

    int count = 0;

    // Добавляем количество дней за каждый год
    for (int y = 1; y < date.year; y++) {
        count += isLeapYear(y) ? 366 : 365;
    }

    // Добавляем количество дней за каждый месяц в данном году
    for (int m = 1; m < date.month; m++) {
        count += daysInMonth[m - 1];
        if (m == 2 && isLeapYear(date.year)) {
            count++; // Дополнительный день в феврале в високосный год
        }
    }

    // Добавляем количество дней в текущем месяце
    count += date.day;

    return count;
}



 
