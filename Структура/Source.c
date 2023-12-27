#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
#include <time.h>
#include "Header.h"

#pragma warning(disable : 4996)

int main() 
{
   
    struct Storage storage;
    storage.count = 0;

    const char* fileName = "FFFF.txt";
    readWorkersFromFile(&storage, fileName);
    setlocale(LC_ALL, "Rus");
    printRecentWorkers(&storage);
    return 0;
}
