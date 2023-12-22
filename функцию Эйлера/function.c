#include <stdio.h>
#include <locale.h>
#include "function.h"


int euler(int n)
{
    setlocale(LC_ALL, "Rus");
    int result = n; // ���������� ����������� ���������� �������� n

    // ���������� ��� ����� �� 2 �� ����� �� n
    for (int i = 2; i * i <= n; i++)
    {
        if (n % i == 0)
        {
            // ����� i �������� ��������� n
            while (n % i == 0) 
            {
                n /= i; // ����� n �� i �� ��� ���, ���� ��� ������� �� i
            }
            result -= result / i; // �������� �� ���������� �������� result/i
        }
    }

    // ���� ����� ����� n > 1, ������ ��� �������� ������� ��������� n
    if (n > 1) 
    {
        result -= result / n;
    }

    return result;
}
