#include <stdio.h>
#include <locale.h>
#include "function.h"



//Например, для числа 36 существует 12 меньших его и взаимно
//простых с ним чисел (1, 5, 7, 11, 13, 17, 19, 23, 25, 29, 31, 35), поэтому 
// euler(36)=12.



int main()
{
    setlocale(LC_ALL, "Rus");
    int n;
    printf("Введите число n: ");
    scanf_s("%d", &n);

    int phi = euler(n);
    printf("Функция Эйлера для числа %d: %d\n", n, phi);

    return 0;
}
