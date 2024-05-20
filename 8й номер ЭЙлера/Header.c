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
    long long length = my_strlen(num);//���������� �������� � ������

    for (int i = 0; i <= length-sequence; i++) //���� ���� �� ����� ������
    {
        long long mult = 1;
        for (int j = 0; j < sequence; j++) //�������� �� 13 ��������� � ������
        {
            mult *= num[i + j] - '0';// ����������� ������ ����� � �������� �������� �� ������� i+j ;
        }
        if (mult > composition) 
        {
            composition = mult;
        }
    }
    printf("Otvet %lld\n", composition);
}

// ������� ��� ��������� ������� ������ ������ �������
void measure_time(void (*func)(const char* , int), const char* num, int sequence) {
    clock_t start, end;
    double time;

    start = clock();
    func(num , sequence); 
    end = clock();

    time = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("TIME: %f sec\n", time);
}