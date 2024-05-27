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
        printf("bn1 ��� bn2 ����� NULL!\n");
        return 1;
    }

    printf("������ �����: ");
    PrintBN(bn1);
    printf("������ �����: ");
    PrintBN(bn2);

    int �����;
    printf("\n�������� �����:\n");
    printf("1. ��������\n");
    printf("2. ���������\n");
    printf("3. ������� bn2 �� bn1\n");
    printf("4. ������� bn1 �� bn2 :\n");
    printf("5. ��������� �� ���������\n");
    scanf_s("%d", &�����);

    switch (�����) {
    case 1:
        printf("\n��������� ��������:\n");
        BigNumber* sum = SumBN(bn1, bn2);
        printf("�����: ");
        PrintBN(sum);
        DeleteBN(&sum);
        break;

    case 2:
        printf("\n��������� ���������:\n");
        BigNumber* mult = MultiplyBN(bn1, bn2);
        printf("������������: ");
        PrintBN(mult);
        DeleteBN(&mult);
        break;

    case 3:
        printf("\n��������� ������� bn2 �� bn1 :\n");
        BigNumber* div = DivideBN(CopyBN(bn2), CopyBN(bn1));
        if (bn1->digits[0] == 0)
        {
            printf("������ (");
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
        
        printf("�������: ");
        PrintBN(div);
        DeleteBN(&div);
        break;


    case 4:
        printf("\n��������� ������� bn1 �� bn2 :\n");
        BigNumber* div1 = DivideBN(CopyBN(bn1), CopyBN(bn2));
        if (bn2->digits[0] == 0)
        {
            printf("������ (");
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
       
        printf("�������: ");
        PrintBN(div1);
        DeleteBN(&div1);
        break;

    case 5:
        printf("������� ��������� ��� ���������:\n");
        int multipass;
        int counter;
        scanf_s("%d", &multipass);
        printf("������� 1-���� ������ �������� �� bn1\n");
        printf("������� 2-���� ������ �������� �� bn2\n");
        scanf_s("%d", &counter);
        if (counter == 1) 
        {
            printf("\n��������� ��������� �� ��������� ���������:\n");
            BigNumber* multonli = MultiplyBNOnli(bn1, multipass);
            printf("������������: ");
            PrintBN(multonli);
            DeleteBN(&multonli);
            break;
        }
        if (counter == 2) {
            printf("\n��������� ��������� �� ��������� ���������:\n");
            BigNumber* multonli = MultiplyBNOnli(bn2, multipass);
            printf("������������: ");
            PrintBN(multonli);
            DeleteBN(&multonli);
            break;
        }
        printf("������� ��������� �������� ��� ������ ��<3");
        break;

    default:
        printf("�������� �����!\n");
        break;
    }

    // �������
    DeleteBN(&bn1);
    DeleteBN(&bn2);

    return 0;
}
