/* HelperFunctions.c */

#include "HelperFunctions.h"
#include <stdio.h>
#pragma warning(disable : 4996)
void clear_input_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}
