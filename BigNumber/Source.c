#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "big_number.h"
#include <locale.h>

int main() {
    setlocale(LC_ALL, "Russian");
    char str1[] = "-22222";
    char str2[] = "-1111";
    BigNumber* bn1 = CreateBN(str1);
    BigNumber* bn2 = CreateBN(str2);

    if (bn1 == NULL || bn2 == NULL) {
        printf("bn1 или bn2 равен NULL!\n");
        return 1;
    }

    printf("Первое число: ");
    PrintBN(bn1);
    printf("Второе число: ");
    PrintBN(bn2);

    int выбор;
    printf("\nСделайте выбор:\n");
    printf("1. Сложение\n");
    printf("2. Умножение\n");
    printf("3. Деление bn2 на bn1\n");
    printf("4. Деление bn1 на bn2 :\n");
    printf("5. Умножение на константу\n");
    scanf_s("%d", &выбор);

    switch (выбор) {
    case 1:
        printf("\nВыполняем сложение:\n");
        BigNumber* sum = SumBN(bn1, bn2);
        printf("Сумма: ");
        PrintBN(sum);
        DeleteBN(&sum);
        break;

    case 2:
        printf("\nВыполняем умножение:\n");
        BigNumber* mult = MultiplyBN(bn1, bn2);
        printf("Произведение: ");
        PrintBN(mult);
        DeleteBN(&mult);
        break;

    case 3:
        printf("\nВыполняем деление bn2 на bn1 :\n");
        BigNumber* div = DivideBN(CopyBN(bn2), CopyBN(bn1));
        if (bn1->digits[0] == 0)
        {
            printf("нельзя (");
            break;
        }
        if (bn1->is_negative == bn2->is_negative)
        {
            div->is_negative = false;

        }
        else
        {
            div->is_negative = true;
        }
        if (div->digits[0] == 0)
        {
            div->is_negative = false;
        }
        
        printf("Частное: ");
        PrintBN(div);
        DeleteBN(&div);
        break;


    case 4:
        printf("\nВыполняем деление bn1 на bn2 :\n");
        BigNumber* div1 = DivideBN(CopyBN(bn1), CopyBN(bn2));
        if (bn2->digits[0] == 0)
        {
            printf("нельзя (");
            break;
        }
        if (bn1->is_negative == bn2->is_negative)
        {
            div1->is_negative = false;
                
        }
        else
        {
            div1->is_negative = true;
        }
        if (div1->digits[0] == 0)
        {
            div1->is_negative = false;
        }
       
        printf("Частное: ");
        PrintBN(div1);
        DeleteBN(&div1);
        break;

    case 5:
        printf("Введите константу для умножения:\n");
        int multipass;
        int counter;
        scanf_s("%d", &multipass);
        printf("Введите 1-если хотите умножить на bn1\n");
        printf("Введите 2-если хотите умножить на bn2\n");
        scanf_s("%d", &counter);
        if (counter == 1) 
        {
            printf("\nВыполняем умножение на введенную константу:\n");
            BigNumber* multonli = MultiplyBNOnli(bn1, multipass);
            printf("Произведение: ");
            PrintBN(multonli);
            DeleteBN(&multonli);
            break;
        }
        if (counter == 2) {
            printf("\nВыполняем умножение на введенную константу:\n");
            BigNumber* multonli = MultiplyBNOnli(bn2, multipass);
            printf("Произведение: ");
            PrintBN(multonli);
            DeleteBN(&multonli);
            break;
        }
        printf("Введите грамотное значение для выбора пж<3");
        break;

    default:
        printf("Неверный выбор!\n");
        break;
    }

    // Очистка
    DeleteBN(&bn1);
    DeleteBN(&bn2);

    return 0;
}
