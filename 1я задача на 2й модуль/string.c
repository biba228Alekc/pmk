#include <stdio.h>
#include <locale.h>
#include "string.h"


#define MAX_LENGTH 100

void inputString(char* str)
{
    printf("������� ������: ");
    fgets(str, MAX_LENGTH, stdin);
}



void Numbers2(const char* str) {
    char* ptr = str; // ��������� �� ������ ������
    while (*ptr) { // ���� �� ��������� ����� ������ ('\0')
        printf("%c%d", *ptr, *ptr); // ����� ������� � ��� ����
        ptr++; // ������� � ���������� �������
    }
}

void Numbers1(const char* str) {
    int i = 0;
    while (str[i] != '\0') {  // ���� �� ��������� ����� ������
        printf("%c%d", str[i], str[i]);  // ������� ������ � ��� ���
        i++;
    }
}

