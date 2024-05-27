#pragma once
#include <stdbool.h>

typedef unsigned char digit;

// Тип большого числа (>10 знаков)
typedef struct BigNumber
{
	size_t size;		// Размер числа
	digit* digits;  	// Массив из цифр числа
	bool is_negative;	// Знак числа
}BigNumber;
/*
* @brief Создание большого числа
* @param number_ : Строка с большим числом
* @return Указатель на выделенную память с большим числом
*/
BigNumber* CreateBN(char* number_);

/*
* @brief Удаляет выбранное большое число
* @param bn_ : Указатель на большое число
*/
void DeleteBN(BigNumber** bn_);

/*
* @brief Печать большого числа
* @param bn_ : Указатель на большое число
*/
void PrintBN(BigNumber* bn_);

/*
* @brief Сумма двух больших чисел
* @param bn1_, bn2_ : Большие числа
* @return Большое число из суммы двух входных
*/
BigNumber* SumBN(BigNumber* bn1_, BigNumber* bn2_);

/*
* @brief Вычитание одного большого числа из другого
* @param bn1_, bn2_ : Большие числа 
* @param result : Результат вычитания
* @return  результат вычитания
*/
BigNumber* Minus(BigNumber* bn1_, BigNumber* bn2_, BigNumber* result);

/*
* @brief Умножение двух больших чисел
* @param bn1, bn2 : Большие числа
* @return Результат умножения
*/
BigNumber* MultiplyBN(BigNumber* bn1, BigNumber* bn2);

/*
* @brief Создание копии большого числа
* @param bn : Большое число для копирования
* @return Копия большого числа
*/
BigNumber* CopyBN(BigNumber* bn);

/*
* @brief Умножение большого числа на целое число
* @param bn : Большое число
* @param num : Целое число
* @return Результат умножения большого числа на целое число
*/
BigNumber* MultiplyBNOnli(BigNumber* bn, int num);

/*
* @brief Вычитание одного большого числа из другого 
* @param bn1_, bn2_ : Большие числа
* @return результат вычитания с инвертированным знаком
*/
BigNumber* MinusreversBN(BigNumber* bn1, BigNumber* bn2);

/*
* @brief Сравнение двух больших чисел
* @param bn1, bn2 : Большие числа для сравнения
* @return Целое число: -1 если bn1 меньше bn2, 0 если они равны, 1 если bn1 больше bn2
*/
int CompareBN(BigNumber* bn1, BigNumber* bn2);

/*
* @brief Деление одного большого числа на другое
* @param dividend : Делимое
* @param divisor : Делитель
* @return Частное от деления
*/
BigNumber* DivideBN(BigNumber* dividend, BigNumber* divisor);
