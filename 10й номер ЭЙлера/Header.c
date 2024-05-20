#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include <stdlib.h>

void sum2(int limit)
{
    // Выделение памяти для массива is_prime и инициализация его значениями false
    bool* is_prime = (bool*)calloc((limit + 1), sizeof(bool));

    // Переменная для хранения суммы простых чисел
    long long sum = 0;

    // Проверка, удалось ли выделить память
    if (is_prime == NULL)
    {
        printf("GG\n"); // Если память не выделена, выводим сообщение об ошибке
    }

    // Инициализация массива is_prime значениями true для всех индексов
    for (int i = 0; i <= limit; ++i)
    {
        is_prime[i] = true;
    }

    // Решето Эратосфена
    for (int p = 2; p * p <= limit; ++p)
    {
        // Если число p простое, отмечаем все кратные p как непростые
        if (is_prime[p] == true)
        {
            for (int i = p * p; i <= limit; i += p)
            {
                is_prime[i] = false;
            }
        }
    }

    // Суммируем все простые числа
    for (int p = 2; p <= limit; ++p)
    {
        if (is_prime[p])
        {
            sum += p;
        }
    }

    // Освобождение выделенной памяти
    free(is_prime);

    // Вывод суммы всех простых чисел меньше двух миллионов
    printf("The sum of all primes is less than two million: %lld\n", sum);
}



bool is_prime(int n)
{
    if (n <= 1)  // Если число меньше или равно 1, то оно не является простым
        return false;
    if (n <= 3)  // Если число равно 2 или 3, то оно простое
        return true;
    if (n % 2 == 0 || n % 3 == 0)  // Если число делится на 2 или 3 без остатка, то оно не простое
        return false;

    // Цикл проверки делителей, начиная с 5
    for (int i = 5; i * i <= n; i += 6)//простые числа, начиная с 5, расположены в форме 6k ± 1 
    {
        // Проверяем делится ли число на i или на (i + 2) без остатка
        if (n % i == 0 || n % (i + 2) == 0)
        {
            return false; // Если делится без остатка, то число не простое
        }
    }

    // Если ни одно из вышеперечисленных условий не выполняется, то число простое
    return true;
}


void sum1(int limit) 
{
    long long sum = 0;

    for (int i = 2; i < limit; ++i)
    {
        if (is_prime(i))
        {
            sum += i;
        }
    }
    printf("The sum of all primes is less than two million: %lld\n", sum);

}

// Функция для измерения времени работы функции
void time_func(void (*func)(int), int limit) {
    clock_t start, end;
    double time;

    start = clock();
    func(limit);
    end = clock();

    time = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("TIME: %f sec\n", time);
}
