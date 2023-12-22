#include <stdio.h>
#include <locale.h>
#include "function.h"


int euler(int n)
{
    setlocale(LC_ALL, "Rus");
    int result = n; // Изначально присваиваем результату значение n

    // Перебираем все числа от 2 до корня из n
    for (int i = 2; i * i <= n; i++)
    {
        if (n % i == 0)
        {
            // Число i является делителем n
            while (n % i == 0) 
            {
                n /= i; // Делим n на i до тех пор, пока оно делится на i
            }
            result -= result / i; // Вычитаем из результата значение result/i
        }
    }

    // Если после цикла n > 1, значит оно является простым делителем n
    if (n > 1) 
    {
        result -= result / n;
    }

    return result;
}
