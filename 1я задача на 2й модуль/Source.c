#include <stdio.h>
#include <locale.h>
#include "string.h"

#define MAX_LENGTH 100


int main() 
{
    setlocale(LC_ALL, "Rus");
    char str[MAX_LENGTH];
    inputString(str);
    Numbers2(str);
 
    return 0;
}