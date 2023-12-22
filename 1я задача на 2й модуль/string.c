#include <stdio.h>
#include <locale.h>
#include "string.h"


#define MAX_LENGTH 100

void inputString(char* str)
{
    printf("Введите строку: ");
    fgets(str, MAX_LENGTH, stdin);
}



void Numbers2(const char* str) {
    char* ptr = str; // Óêàçàòåëü íà íà÷àëî ñòðîêè
    while (*ptr) { // Ïîêà íå äîñòèãíóò êîíåö ñòðîêè ('\0')
        printf("%c%d", *ptr, *ptr); // Âûâîä ñèìâîëà è åãî êîäà
        ptr++; // Ïåðåõîä ê ñëåäóþùåìó ñèìâîëó
    }
}

void Numbers1(const char* str) {
    int i = 0;
    while (str[i] != '\0') {  // Ïîêà íå äîñòèãíóò êîíåö ñòðîêè
        printf("%c%d", str[i], str[i]);  // Âûâîäèì ñèìâîë è åãî êîä
        i++;
    }
}

