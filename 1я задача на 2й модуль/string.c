#include <stdio.h>
#include <locale.h>
#include "string.h"


#define MAX_LENGTH 100

void inputString(char* str)
{
    printf("Введите строку: ");
    fgets(str, MAX_LENGTH, stdin);
}



void Numbers2(const char* str) {
    char* ptr = str; // Указатель на начало строки
    while (*ptr) { // Пока не достигнут конец строки ('\0')
        printf("%c%d", *ptr, *ptr); // Вывод символа и его кода
        ptr++; // Переход к следующему символу
    }
}

void Numbers1(const char* str) {
    int i = 0;
    while (str[i] != '\0') {  // Пока не достигнут конец строки
        printf("%c%d", str[i], str[i]);  // Выводим символ и его код
        i++;
    }
}

