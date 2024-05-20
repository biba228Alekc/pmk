#include <stdio.h>
#include <time.h>
void func(int sum) {
    int a, b, c;

    for (a = 1; a < sum; a++) {
        for (b = a + 1; b < sum; b++) {
            c = sum - a - b;
            if (a * a + b * b == c * c)
            {
                printf("The Pythagorean Triple: a = %d, b = %d, c = %d\n", a, b, c);
                printf("Composition abc: %d\n", a * b * c);

            }
        }
    }

    printf("GG\n");
}

// Функция для измерения времени работы функции
void time_func(void (*func)(int), int sum) {
    clock_t start, end;
    double time;

    start = clock();
    func(sum);
    end = clock();

    time = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("TIME: %f sec\n", time);
}
