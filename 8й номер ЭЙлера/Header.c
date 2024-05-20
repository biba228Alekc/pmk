#include <stdio.h>
#include <string.h>
#include <time.h>


long long my_strlen(const char* str) {
    long long length = 0;

    while (str[length] != '\0') {
        length++;
    }

    return length;
}


void calculate_composition(const char* num, int sequence) {
    long long composition = 0;
    long long length = my_strlen(num);//количество символов в строке

    for (int i = 0; i <= length-sequence; i++)
    {
        long long mult = 1;
        for (int j = 0; j < sequence; j++) //умножает по 13 элементов в строке
        {
            mult *= num[i + j] - '0';// преобразует символ цифры в числовое значение по индексу i+j 
        }
        if (mult > composition) 
        {
            composition = mult;
        }
    }
    printf("Otvet %lld\n", composition);
}

// Функция для измерения времени работы другой функции
void time_func(void (*func)(const char* , int), const char* num, int sequence) 
{
    clock_t start, end;
    double time;

    start = clock();
    func(num , sequence); 
    end = clock();

    time = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("TIME: %f sec\n", time);
}
