#include "big_number.h"

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "my_string.h"

#pragma warning(disable : 4996)

BigNumber* CreateBN(char* number_)
{
	if (number_ == NULL || strlen(number_) == 0 ||
		!IsIntString(number_))
		return NULL;

	BigNumber* bn = (BigNumber*)malloc(sizeof(BigNumber));
	if (bn == NULL)
		return NULL;

	size_t size = strlen(number_);
	if (*number_ == '-')
	{
		bn->size = size - 1;
		bn->is_negative = true;
		number_++;
	}
	else
	{
		bn->size = size;
		bn->is_negative = false;
	}

	bn->digits = (digit*)calloc(bn->size, sizeof(digit));
	if (bn->digits == NULL)
	{
		free(bn);
		return NULL;
	}

	for (size_t i = 0; i < bn->size; ++i)
		bn->digits[i] = number_[i] - '0';

	return bn;
}




void DeleteBN(BigNumber** bn_)
{
	free((*bn_)->digits);
	free(*bn_);

	*bn_ = NULL;
}

void PrintBN(BigNumber* bn_)
{
	if (bn_ == NULL)
	{
		printf("BigNumber is empty!\n");
		return;
	}

	if (bn_->is_negative)
		printf("-");

	for (size_t i = 0; i < bn_->size; ++i)
		printf("%u", bn_->digits[i]);

	printf("\n");
}




BigNumber* SumBN(BigNumber* bn1_, BigNumber* bn2_)
{
    // Проверка на NULL входных данных, если одно из чисел NULL, возвращаем NULL
    if (bn1_ == NULL || bn2_ == NULL)
        return NULL;

    // Размеры чисел bn1_ и bn2_
    size_t size1 = bn1_->size; // Размер первого числа
    size_t size2 = bn2_->size; // Размер второго числа
    size_t max_size = (size1 > size2) ? size1 : size2; // Находим максимальный размер из двух чисел
    size_t result_size = max_size + 1; // Размер результата сложения, может быть на 1 больше из-за переноса

    // Выделение памяти для результата
    BigNumber* result = (BigNumber*)malloc(sizeof(BigNumber)); // Создаем структуру для результата
    if (result == NULL)
        return NULL; // Если память не выделена, возвращаем NULL

    // Выделяем память для цифр результата и инициализируем их нулями
    result->digits = (digit*)calloc(result_size, sizeof(digit)); // Массив цифр для результата
    if (result->digits == NULL)
    {
        free(result); // Если память не выделена, освобождаем структуру и возвращаем NULL
        return NULL;
    }

    result->size = result_size; // Устанавливаем размер результата

    // Если числа разных знаков, выполняем вычитание
    if (bn1_->is_negative != bn2_->is_negative)
    {
        if (bn1_->is_negative)
        {
            bn1_->is_negative = false; // Изменяем знак первого числа на положительный
            result = Minus(bn2_, bn1_, result); // Вычитаем из второго первое (bn2_ - bn1_)
        }
        else
        {
            bn2_->is_negative = false; // Изменяем знак второго числа на положительный
            result = Minus(bn1_, bn2_, result); // Вычитаем из первого второе (bn1_ - bn2_)
        }
    }
    else // Если числа одного знака, выполняем сложение
    {
        int carry = 0; // Переменная для хранения переноса при сложении
        for (int i = 0; i < max_size; ++i)
        {
            // Получаем соответствующие цифры из bn1_ и bn2_, или 0 если индекс превышает размер числа
            int digit1 = (i < size1) ? bn1_->digits[size1 - 1 - i] : 0; // Цифра из первого числа
            int digit2 = (i < size2) ? bn2_->digits[size2 - 1 - i] : 0; // Цифра из второго числа
            int sum = digit1 + digit2 + carry; // Суммируем цифры и перенос
            result->digits[result_size - 1 - i] = sum % 10; // Записываем последнюю цифру суммы в результат
            carry = sum / 10; // Обновляем перенос
        }

        if (carry)
            result->digits[0] = carry; // Если есть перенос, записываем его в начало массива цифр
        else
        {
            size_t new_size = result_size - 1; // Если нет переноса, уменьшаем размер результата
            digit* new_digits = (digit*)calloc(new_size, sizeof(digit)); // Выделяем новую память для цифр
            for (size_t i = 0; i < new_size; ++i)
                new_digits[i] = result->digits[i + 1]; // Копируем цифры без ведущего нуля
            free(result->digits); // Освобождаем старую память
            result->digits = new_digits; // Обновляем указатель на цифры
            result->size = new_size; // Обновляем размер результата
        }

        result->is_negative = bn1_->is_negative; // Знак результата такой же, как у исходных чисел
    }

    return result; // Возвращаем результат
}






BigNumber* Minus(BigNumber* bn1_, BigNumber* bn2_, BigNumber* result)
{
    // Размеры чисел bn1_ и bn2_
    size_t size1 = bn1_->size; // Размер первого числа
    size_t size2 = bn2_->size; // Размер второго числа
    size_t max_size = (size1 > size2) ? size1 : size2; // Находим максимальный размер из двух чисел

    // Инициализируем массив цифр результата нулями
    memset(result->digits, 0, result->size);

    bool is_negative = false; // Переменная для хранения знака результата
    bool swap = false; // Переменная для отслеживания обмена чисел

    // Проверяем, нужно ли менять местами числа
    if (size1 < size2 || (size1 == size2 && memcmp(bn1_->digits, bn2_->digits, size1) < 0))
    {
        BigNumber* temp = bn1_; // Временная переменная для обмена
        bn1_ = bn2_; // Меняем местами первое и второе число
        bn2_ = temp; // Устанавливаем второе число как первое
        swap = true; // Отмечаем факт обмена
    }

    int borrow = 0; // Переменная для хранения заема при вычитании
    for (int i = 0; i < max_size; ++i)
    {
        // Получаем соответствующие цифры из bn1_ и bn2_, или 0 если индекс превышает размер числа
        int digit1 = (i < bn1_->size) ? bn1_->digits[bn1_->size - 1 - i] : 0; // Цифра из первого числа
        int digit2 = (i < bn2_->size) ? bn2_->digits[bn2_->size - 1 - i] : 0; // Цифра из второго числа
        int sub = digit1 - digit2 - borrow; // Выполняем вычитание с учетом заема

        if (sub < 0) // Если результат отрицательный, берем заем
        {
            sub += 10; // Добавляем 10 к результату
            borrow = 1; // Устанавливаем заем
        }
        else
        {
            borrow = 0; // Сбрасываем заем
        }

        result->digits[result->size - 1 - i] = sub; // Записываем результат в массив цифр результата
    }

    result->is_negative = swap; // Знак результата зависит от факта обмена

    // Удаляем ведущие нули
    size_t non_zero_index = 0;
    while (non_zero_index < result->size && result->digits[non_zero_index] == 0)
        non_zero_index++;

    if (non_zero_index == result->size) // Если все цифры равны нулю
    {
        result->size = 1;
        result->digits[0] = 0; // Результат равен нулю
    }
    else // Если есть ненулевые цифры
    {
        size_t new_size = result->size - non_zero_index; // Новый размер массива цифр
        digit* new_digits = (digit*)calloc(new_size, sizeof(digit)); // Выделяем новую память для цифр
        for (size_t i = 0; i < new_size; ++i)
            new_digits[i] = result->digits[non_zero_index + i]; // Копируем ненулевые цифры
        free(result->digits); // Освобождаем старую память
        result->digits = new_digits; // Обновляем указатель на цифры
        result->size = new_size; // Обновляем размер результата
    }

    return result; // Возвращаем результат
}



BigNumber* CopyBN(BigNumber* bn) {
    if (bn == NULL) {
        return NULL; // Если входной указатель равен NULL, возвращаем NULL
    }

    // Выделяем память для новой структуры BigNumber
    BigNumber* copy = (BigNumber*)malloc(sizeof(BigNumber));
    if (copy == NULL) {
        return NULL; // Если не удалось выделить память, возвращаем NULL
    }

    // Копируем размер и знак из оригинальной структуры в новую
    copy->size = bn->size; // Копируем размер числа
    copy->is_negative = bn->is_negative; // Копируем знак числа

    // Выделяем память для массива цифр в новой структуре
    copy->digits = (digit*)calloc(copy->size, sizeof(digit));
    if (copy->digits == NULL) {
        free(copy); // Если не удалось выделить память для массива цифр, освобождаем память для структуры и возвращаем NULL
        return NULL;
    }

    // Копируем массив цифр из оригинальной структуры в новую
    memcpy(copy->digits, bn->digits, copy->size * sizeof(digit));

    return copy; // Возвращаем указатель на новую структуру BigNumber
}

BigNumber* MultiplyBN(BigNumber* bn1, BigNumber* bn2)
{
    // Проверяем, что входные аргументы не равны NULL
    if (bn1 == NULL || bn2 == NULL)
        return NULL;

    // Проверка, если одно из чисел равно нулю
    if ((bn1->size == 1 && bn1->digits[0] == 0) || (bn2->size == 1 && bn2->digits[0] == 0)) {
        // Создаем объект BigNumber для результата
        BigNumber* zero_result = CreateBN("0");

        // Устанавливаем знак результата
        zero_result->is_negative = false;

        return zero_result;
    }

    // Определяем знак результата
    bool is_negative = bn1->is_negative != bn2->is_negative;

    // Выделяем память для результата
    size_t result_size = bn1->size + bn2->size;
    BigNumber* result = (BigNumber*)malloc(sizeof(BigNumber));
    if (result == NULL)
        return NULL;

    // Выделяем память под массив цифр результата
    result->digits = (digit*)calloc(result_size, sizeof(digit));
    if (result->digits == NULL)
    {
        free(result);
        return NULL;
    }
    result->size = result_size;
    result->is_negative = is_negative;

    // Умножаем числа "столбиком"
    for (int i = bn1->size - 1; i >= 0; --i)
    {
        int carry = 0;
        for (int j = bn2->size - 1; j >= 0; --j)
        {
            // Умножаем цифры из bn1 и bn2, учитывая текущий разряд результата и перенос
            int product = bn1->digits[i] * bn2->digits[j] + result->digits[i + j + 1] + carry;
            result->digits[i + j + 1] = product % 10;
            carry = product / 10;
        }
        result->digits[i] += carry; // Добавляем оставшийся перенос к текущему разряду
    }

    // Удаляем ведущие нули из результата
    size_t non_zero_index = 0;
    while (non_zero_index < result_size && result->digits[non_zero_index] == 0)
        non_zero_index++;

    // Если все цифры нулевые, устанавливаем размер результата в 1 и значение равное 0
    if (non_zero_index == result_size)
    {
        result->size = 1;
        result->digits[0] = 0;
    }
    else
    {
        // Создаем новый массив для хранения значащих цифр
        result->size -= non_zero_index;
        memmove(result->digits, result->digits + non_zero_index, result->size);
    }

    return result;
}


BigNumber* MultiplyBNOnli(BigNumber* bn, int num)
{
    if (bn == NULL)
    {
        return NULL; // Если входной указатель равен NULL, возвращаем NULL
    }

    // Определяем знак результата умножения
    // Если знаки bn и num различаются, результат отрицательный
    bool is_negative = (bn->is_negative && num > 0) || (!bn->is_negative && num < 0);

    // Приводим num к неотрицательному значению для упрощения расчетов
    num = abs(num);

    // Если num равен 0, результатом умножения является 0
    if (num == 0)
    {
        char zero[] = "0";
        return CreateBN(zero); // Создаем BigNumber, представляющий 0, и возвращаем его
    }

    int carry = 0; // Переменная для переноса при умножении
    size_t result_size = bn->size + 1; // Размер результата умножения на единицу больше, чем у исходного числа
    BigNumber* result = (BigNumber*)malloc(sizeof(BigNumber)); // Выделяем память для результата
    if (result == NULL)
    {
        return NULL; // Если не удалось выделить память, возвращаем NULL
    }

    // Выделяем память для массива цифр в результате и инициализируем его нулями
    result->digits = (digit*)calloc(result_size, sizeof(digit));
    if (result->digits == NULL)
    {
        free(result); // Если не удалось выделить память для массива цифр, освобождаем память для структуры и возвращаем NULL
        return NULL;
    }
    result->size = result_size; // Устанавливаем размер результата
    result->is_negative = is_negative; // Устанавливаем знак результата

    // Выполняем умножение столбиком, начиная с младших цифр
    for (int i = bn->size - 1; i >= 0; --i)
    {
        // Умножаем текущую цифру на num и добавляем перенос
        int product = bn->digits[i] * num + carry;
        result->digits[i + 1] = product % 10; // Остаток от деления на 10 - текущая цифра результата
        carry = product / 10; // Перенос для следующей итерации
    }

    result->digits[0] = carry; // Перенос становится старшей цифрой результата

    // Удаляем ведущие нули, если они есть
    if (result->digits[0] == 0)
    {
        // Сдвигаем все цифры на одну позицию влево
        memmove(result->digits, result->digits + 1, result_size - 1);
        result->size--; // Уменьшаем размер результата на 1
    }

    return result; // Возвращаем указатель на результат
}


int CompareBN(BigNumber* bn1, BigNumber* bn2)
{
    // Если одно из чисел NULL, считаем, что оно меньше
    if (bn1 == NULL && bn2 == NULL)
        return 0; // Оба числа равны, возвращаем 0
    else if (bn1 == NULL)
        return -1; // Число bn1 отсутствует, считаем, что bn2 больше, возвращаем -1
    else if (bn2 == NULL)
        return 1; // Число bn2 отсутствует, считаем, что bn1 больше, возвращаем 1

    // Проверка на равенство знаков
    if (bn1->is_negative && !bn2->is_negative)
        return -1; // bn1 отрицательное, bn2 положительное, считаем bn1 меньше, возвращаем -1
    else if (!bn1->is_negative && bn2->is_negative)
        return 1; // bn1 положительное, bn2 отрицательное, считаем bn1 больше, возвращаем 1

    // Сравнение по модулю
    if (bn1->size > bn2->size)
        return bn1->is_negative ? -1 : 1; // Размер bn1 больше, считаем bn1 меньше, если отрицательное, и больше, если положительное
    else if (bn1->size < bn2->size)
        return bn1->is_negative ? 1 : -1; // Размер bn2 больше, считаем bn1 больше, если отрицательное, и меньше, если положительное

    // Размеры равны, поэлементное сравнение
    for (size_t i = 0; i < bn1->size; ++i)
    {
        if (bn1->digits[i] > bn2->digits[i])
            return bn1->is_negative ? -1 : 1; // Цифра в bn1 больше, считаем bn1 меньше, если отрицательное, и больше, если положительное
        else if (bn1->digits[i] < bn2->digits[i])
            return bn1->is_negative ? 1 : -1; // Цифра в bn2 больше, считаем bn1 больше, если отрицательное, и меньше, если положительное
    }

    // Числа равны
    return 0; // Оба числа равны, возвращаем 0
}


BigNumber* MinusreversBN(BigNumber* bn1, BigNumber* bn2)
{
    // Проверяем, что входные аргументы не равны NULL
    if (bn1 == NULL || bn2 == NULL)
        return NULL;

    // Определяем максимальный размер результата
    size_t max_size = (bn1->size > bn2->size) ? bn1->size : bn2->size;

    // Выделяем память для результата
    BigNumber* result = (BigNumber*)malloc(sizeof(BigNumber));
    if (result == NULL)
        return NULL;

    // Выделяем память под массив цифр результата
    result->digits = (digit*)calloc(max_size, sizeof(digit));
    if (result->digits == NULL)
    {
        free(result);
        return NULL;
    }
    result->size = max_size;

    // Если числа разных знаков, выполняем сложение
    if (bn1->is_negative != bn2->is_negative)
    {
        // Изменяем знак второго числа и выполняем сложение
        bn2->is_negative = !bn2->is_negative;
        result = SumBN(bn1, bn2);
        bn2->is_negative = !bn2->is_negative; // Возвращаем знак второго числа
    }
    else // Если числа одного знака, выполняем вычитание
    {
        bool swap = false;

        // Проверяем, какое число по модулю больше
        if (bn1->size < bn2->size || (bn1->size == bn2->size && memcmp(bn1->digits, bn2->digits, bn1->size) < 0))
        {
            // Меняем местами числа и помечаем, что выполняется обмен
            BigNumber* temp = bn1;
            bn1 = bn2;
            bn2 = temp;
            swap = true;
        }

        int borrow = 0;
        for (size_t i = 0; i < max_size; ++i)
        {
            // Получаем цифры из чисел bn1 и bn2, учитывая выравнивание по разрядам
            int digit1 = (i < bn1->size) ? bn1->digits[bn1->size - 1 - i] : 0;
            int digit2 = (i < bn2->size) ? bn2->digits[bn2->size - 1 - i] : 0;

            // Вычитаем цифры с учетом заема
            int diff = digit1 - digit2 - borrow;

            // Если разность отрицательная, добавляем 10 и устанавливаем заем
            if (diff < 0)
            {
                diff += 10;
                borrow = 1;
            }
            else
            {
                borrow = 0;
            }

            // Записываем разность в соответствующий разряд результата
            result->digits[max_size - 1 - i] = diff;
        }

        // Устанавливаем знак результата в зависимости от факта обмена
        result->is_negative = swap;

        // Удаляем ведущие нули из результата
        size_t non_zero_index = 0;
        while (non_zero_index < result->size && result->digits[non_zero_index] == 0)
            non_zero_index++;

        // Если все цифры нулевые, устанавливаем размер результата в 1 и значение равное 0
        if (non_zero_index == result->size)
        {
            result->size = 1;
            result->digits[0] = 0;
        }
        else
        {
            // Создаем новый массив для хранения значащих цифр
            size_t new_size = result->size - non_zero_index;
            digit* new_digits = (digit*)calloc(new_size, sizeof(digit));

            // Копируем значащие цифры в новый массив
            for (size_t i = 0; i < new_size; ++i)
                new_digits[i] = result->digits[non_zero_index + i];

            // Освобождаем старый массив и устанавливаем новый массив и размер в результат
            free(result->digits);
            result->digits = new_digits;
            result->size = new_size;
        }
    }

    // Возвращаем результат вычитания
    return result;
}


BigNumber* DivideBN(BigNumber* dividend, BigNumber* divisor)
{
    // Проверка входных данных
    if (dividend == NULL || divisor == NULL || divisor->size == 0 || (divisor->size == 1 && divisor->digits[0] == 0))
        return NULL;

    // Проверка на деление на ноль или деление нуля
    if ((divisor->size == 1 && divisor->digits[0] == 0) || (dividend->size == 1 && dividend->digits[0] == 0))
    {
        BigNumber* zero = CreateBN("0"); // Создание объекта BigNumber для числа 0
        return zero; // Возвращаем указатель на объект, представляющий число 0
    }

    // Создание копий чисел, чтобы работать с их абсолютными значениями
    BigNumber* abs_dividend = CopyBN(dividend); // Создание копии делимого
    BigNumber* abs_divisor = CopyBN(divisor);   // Создание копии делителя
    if (abs_dividend == NULL || abs_divisor == NULL)
    {
        DeleteBN(&abs_dividend); // Освобождение памяти, если создание копии не удалось
        DeleteBN(&abs_divisor);  // Освобождение памяти, если создание копии не удалось
        return NULL;
    }
    abs_dividend->is_negative = false; // Установка знака копии делимого как положительный
    abs_divisor->is_negative = false;  // Установка знака копии делителя как положительный

    // Создание пустого результата деления
    BigNumber* quotient = CreateBN("0"); // Создание объекта BigNumber для хранения результата деления
    if (quotient == NULL)
    {
        DeleteBN(&abs_dividend); // Освобождение памяти, если создание результата не удалось
        DeleteBN(&abs_divisor);  // Освобождение памяти, если создание результата не удалось
        return NULL;
    }

    // Создание копии делимого для использования в цикле деления
    BigNumber* remainder = CopyBN(abs_dividend); // Создание копии делимого для использования в цикле деления
    if (remainder == NULL)
    {
        DeleteBN(&quotient);      // Освобождение памяти, если создание копии делимого не удалось
        DeleteBN(&abs_dividend);  // Освобождение памяти, если создание копии делимого не удалось
        DeleteBN(&abs_divisor);   // Освобождение памяти, если создание копии делимого не удалось
        return NULL;
    }

    // Проверка на равенство нулю делимого
    if (CompareBN(abs_dividend, CreateBN("0")) == 0)
    {
        DeleteBN(&abs_divisor); // Освобождение памяти, если делимое равно нулю
        return quotient;        // Возвращаем нулевой результат
    }

    // Проверка на равенство делителю делимого
    if (CompareBN(abs_divisor, abs_dividend) == 0)
    {
        DeleteBN(&abs_divisor);  // Освобождение памяти, если делитель равен делимому
        DeleteBN(&remainder);    // Освобождение памяти, если делитель равен делимому
        quotient->digits[0] = 1; // Устанавливаем единицу в результате деления
        return quotient;         // Возвращаем результат деления
    }

    // Проверка, что делитель больше делимого
    if (CompareBN(abs_divisor, abs_dividend) > 0)
    {
        DeleteBN(&abs_divisor); // Освобождение памяти, если делитель больше делимого
        DeleteBN(&remainder);   // Освобождение памяти, если делитель больше делимого
        return quotient;        // Возвращаем нулевой результат
    }

    // Пока остаток больше или равен делителю, продолжаем деление
    while (CompareBN(remainder, abs_divisor) >= 0)
    {
        // Инициализация счетчика для подсчета количества вычитаний
        int count = 0;

        // Вычитаем делитель из остатка столько раз, пока остаток больше или равен делителю
        while (CompareBN(remainder, abs_divisor) >= 0)
        {
            // Вычитаем делитель из остатка
            BigNumber* subtracted = MinusreversBN(remainder, abs_divisor); // Вычитание делителя из остатка
            DeleteBN(&remainder); // Освобождаем память, выделенную под предыдущий остаток
            remainder = subtracted; // Об
            // Увеличиваем счетчик
            count++;
        }

        // Преобразуем количество вычитаний в "цифру" результата деления и добавляем ее к результату
        char count_str[12]; // Максимальная длина цифры - 10 символов
        sprintf(count_str, "%d", count); // Преобразуем количество вычитаний в строку
        BigNumber* count_bn = CreateBN(count_str); // Создаем BigNumber для хранения результата вычитаний
        BigNumber* temp_quotient = MultiplyBNOnli(quotient, 10); // Умножаем текущий результат деления на 10
        BigNumber* new_quotient = SumBN(temp_quotient, count_bn); // Добавляем цифру к результату деления
        DeleteBN(&count_bn); // Освобождаем память, выделенную под объект count_bn
        DeleteBN(&temp_quotient); // Освобождаем память, выделенную под объект temp_quotient
        DeleteBN(&quotient); // Освобождаем память, выделенную под предыдущий результат деления
        quotient = new_quotient; // Обновляем результат деления
    }

    // Освобождаем память, занимаемую остатком и временным делителем
    DeleteBN(&remainder); // Освобождаем память, выделенную под остаток
    DeleteBN(&abs_divisor); // Освобождаем память, выделенную под делитель
    DeleteBN(&abs_dividend); // Освобождаем память, выделенную под делимое

    return quotient; // Возвращаем результат деления
}

