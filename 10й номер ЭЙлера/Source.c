#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include <stdlib.h>
#include "Header.h"

#define LIMIT 2000000

int main()
{
    int limit = LIMIT;
    time_func(sum1, limit);
    time_func(sum2, limit);

   
    return 0;
}
