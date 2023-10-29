#include "functions.h"
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <locale.h>

#define DIGITS 4


void generateSecretNumber(int secret[])
{
    srand(time(NULL));

    secret[0] = rand() % 9 + 1; // Ãåíåðèðóåì ïåðâóþ öèôðó îò 1 äî 9

    for (int i = 1; i < DIGITS; i++) {
        int digit;
        do {
            digit = rand() % 10; // Ãåíåðèðóåì îñòàëüíûå öèôðû îò 0 äî 9
        } while (!isValidDigit(secret, i, digit)); // Óáåæäàåìñÿ, ÷òî öèôðû óíèêàëüíû

        secret[i] = digit; // Çàïèñûâàåì ñãåíåðèðîâàííóþ öèôðó
    }
}


int isValidDigit(int secret[], int index, int digit) {
    for (int i = 0; i < index; i++) {
        if (secret[i] == digit) {
            return 0; // Öèôðà óæå ïðèñóòñòâóåò â ÷èñëå
        }
    }
    return 1; // Âñå öèôðû óíèêàëüíû
}


void calculateBullsAndCows(int secret[], int guess[], int* bulls, int* cows) {
    *bulls = 0;
    *cows = 0;

    for (int i = 0; i < DIGITS; i++) {
        if (secret[i] == guess[i]) {
            (*bulls)++; // Åñëè öèôðà ñîâïàäàåò ïî ïîçèöèè, óâåëè÷èâàåì êîëè÷åñòâî áûêîâ
        }
        else {
            for (int j = 0; j < DIGITS; j++) {
                if (secret[i] == guess[j]) {
                    (*cows)++; // Óâåëè÷èâàåì êîëè÷åñòâî êîðîâ
                    break;
                }
            }
        }
    }
}
