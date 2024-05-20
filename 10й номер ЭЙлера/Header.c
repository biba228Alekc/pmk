#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include <stdlib.h>

void sum2(int limit)
{
    // ��������� ������ ��� ������� is_prime � ������������� ��� ���������� false
    bool* is_prime = (bool*)calloc((limit + 1), sizeof(bool));

    // ���������� ��� �������� ����� ������� �����
    long long sum = 0;

    // ��������, ������� �� �������� ������
    if (is_prime == NULL)
    {
        printf("GG\n"); // ���� ������ �� ��������, ������� ��������� �� ������
    }

    // ������������� ������� is_prime ���������� true ��� ���� ��������
    for (int i = 0; i <= limit; ++i)
    {
        is_prime[i] = true;
    }

    // ������ ����������
    for (int p = 2; p * p <= limit; ++p)
    {
        // ���� ����� p �������, �������� ��� ������� p ��� ���������
        if (is_prime[p] == true)
        {
            for (int i = p * p; i <= limit; i += p)
            {
                is_prime[i] = false;
            }
        }
    }

    // ��������� ��� ������� �����
    for (int p = 2; p <= limit; ++p)
    {
        if (is_prime[p])
        {
            sum += p;
        }
    }

    // ������������ ���������� ������
    free(is_prime);

    // ����� ����� ���� ������� ����� ������ ���� ���������
    printf("The sum of all primes is less than two million: %lld\n", sum);
}



bool is_prime(int n)
{
    if (n <= 1)  // ���� ����� ������ ��� ����� 1, �� ��� �� �������� �������
        return false;
    if (n <= 3)  // ���� ����� ����� 2 ��� 3, �� ��� �������
        return true;
    if (n % 2 == 0 || n % 3 == 0)  // ���� ����� ������� �� 2 ��� 3 ��� �������, �� ��� �� �������
        return false;

    // ���� �������� ���������, ������� � 5
    for (int i = 5; i * i <= n; i += 6)//������� �����, ������� � 5, ����������� � ����� 6k � 1 
    {
        // ��������� ������� �� ����� �� i ��� �� (i + 2) ��� �������
        if (n % i == 0 || n % (i + 2) == 0)
        {
            return false; // ���� ������� ��� �������, �� ����� �� �������
        }
    }

    // ���� �� ���� �� ����������������� ������� �� �����������, �� ����� �������
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

// ������� ��� ��������� ������� ������ �������
void time_func(void (*func)(int), int limit) {
    clock_t start, end;
    double time;

    start = clock();
    func(limit);
    end = clock();

    time = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("TIME: %f sec\n", time);
}
