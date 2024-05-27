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
    // �������� �� NULL ������� ������, ���� ���� �� ����� NULL, ���������� NULL
    if (bn1_ == NULL || bn2_ == NULL)
        return NULL;

    // ������� ����� bn1_ � bn2_
    size_t size1 = bn1_->size; // ������ ������� �����
    size_t size2 = bn2_->size; // ������ ������� �����
    size_t max_size = (size1 > size2) ? size1 : size2; // ������� ������������ ������ �� ���� �����
    size_t result_size = max_size + 1; // ������ ���������� ��������, ����� ���� �� 1 ������ ��-�� ��������

    // ��������� ������ ��� ����������
    BigNumber* result = (BigNumber*)malloc(sizeof(BigNumber)); // ������� ��������� ��� ����������
    if (result == NULL)
        return NULL; // ���� ������ �� ��������, ���������� NULL

    // �������� ������ ��� ���� ���������� � �������������� �� ������
    result->digits = (digit*)calloc(result_size, sizeof(digit)); // ������ ���� ��� ����������
    if (result->digits == NULL)
    {
        free(result); // ���� ������ �� ��������, ����������� ��������� � ���������� NULL
        return NULL;
    }

    result->size = result_size; // ������������� ������ ����������

    // ���� ����� ������ ������, ��������� ���������
    if (bn1_->is_negative != bn2_->is_negative)
    {
        if (bn1_->is_negative)
        {
            bn1_->is_negative = false; // �������� ���� ������� ����� �� �������������
            result = Minus(bn2_, bn1_, result); // �������� �� ������� ������ (bn2_ - bn1_)
        }
        else
        {
            bn2_->is_negative = false; // �������� ���� ������� ����� �� �������������
            result = Minus(bn1_, bn2_, result); // �������� �� ������� ������ (bn1_ - bn2_)
        }
    }
    else // ���� ����� ������ �����, ��������� ��������
    {
        int carry = 0; // ���������� ��� �������� �������� ��� ��������
        for (int i = 0; i < max_size; ++i)
        {
            // �������� ��������������� ����� �� bn1_ � bn2_, ��� 0 ���� ������ ��������� ������ �����
            int digit1 = (i < size1) ? bn1_->digits[size1 - 1 - i] : 0; // ����� �� ������� �����
            int digit2 = (i < size2) ? bn2_->digits[size2 - 1 - i] : 0; // ����� �� ������� �����
            int sum = digit1 + digit2 + carry; // ��������� ����� � �������
            result->digits[result_size - 1 - i] = sum % 10; // ���������� ��������� ����� ����� � ���������
            carry = sum / 10; // ��������� �������
        }

        if (carry)
            result->digits[0] = carry; // ���� ���� �������, ���������� ��� � ������ ������� ����
        else
        {
            size_t new_size = result_size - 1; // ���� ��� ��������, ��������� ������ ����������
            digit* new_digits = (digit*)calloc(new_size, sizeof(digit)); // �������� ����� ������ ��� ����
            for (size_t i = 0; i < new_size; ++i)
                new_digits[i] = result->digits[i + 1]; // �������� ����� ��� �������� ����
            free(result->digits); // ����������� ������ ������
            result->digits = new_digits; // ��������� ��������� �� �����
            result->size = new_size; // ��������� ������ ����������
        }

        result->is_negative = bn1_->is_negative; // ���� ���������� ����� ��, ��� � �������� �����
    }

    return result; // ���������� ���������
}






BigNumber* Minus(BigNumber* bn1_, BigNumber* bn2_, BigNumber* result)
{
    // ������� ����� bn1_ � bn2_
    size_t size1 = bn1_->size; // ������ ������� �����
    size_t size2 = bn2_->size; // ������ ������� �����
    size_t max_size = (size1 > size2) ? size1 : size2; // ������� ������������ ������ �� ���� �����

    // �������������� ������ ���� ���������� ������
    memset(result->digits, 0, result->size);

    bool is_negative = false; // ���������� ��� �������� ����� ����������
    bool swap = false; // ���������� ��� ������������ ������ �����

    // ���������, ����� �� ������ ������� �����
    if (size1 < size2 || (size1 == size2 && memcmp(bn1_->digits, bn2_->digits, size1) < 0))
    {
        BigNumber* temp = bn1_; // ��������� ���������� ��� ������
        bn1_ = bn2_; // ������ ������� ������ � ������ �����
        bn2_ = temp; // ������������� ������ ����� ��� ������
        swap = true; // �������� ���� ������
    }

    int borrow = 0; // ���������� ��� �������� ����� ��� ���������
    for (int i = 0; i < max_size; ++i)
    {
        // �������� ��������������� ����� �� bn1_ � bn2_, ��� 0 ���� ������ ��������� ������ �����
        int digit1 = (i < bn1_->size) ? bn1_->digits[bn1_->size - 1 - i] : 0; // ����� �� ������� �����
        int digit2 = (i < bn2_->size) ? bn2_->digits[bn2_->size - 1 - i] : 0; // ����� �� ������� �����
        int sub = digit1 - digit2 - borrow; // ��������� ��������� � ������ �����

        if (sub < 0) // ���� ��������� �������������, ����� ����
        {
            sub += 10; // ��������� 10 � ����������
            borrow = 1; // ������������� ����
        }
        else
        {
            borrow = 0; // ���������� ����
        }

        result->digits[result->size - 1 - i] = sub; // ���������� ��������� � ������ ���� ����������
    }

    result->is_negative = swap; // ���� ���������� ������� �� ����� ������

    // ������� ������� ����
    size_t non_zero_index = 0;
    while (non_zero_index < result->size && result->digits[non_zero_index] == 0)
        non_zero_index++;

    if (non_zero_index == result->size) // ���� ��� ����� ����� ����
    {
        result->size = 1;
        result->digits[0] = 0; // ��������� ����� ����
    }
    else // ���� ���� ��������� �����
    {
        size_t new_size = result->size - non_zero_index; // ����� ������ ������� ����
        digit* new_digits = (digit*)calloc(new_size, sizeof(digit)); // �������� ����� ������ ��� ����
        for (size_t i = 0; i < new_size; ++i)
            new_digits[i] = result->digits[non_zero_index + i]; // �������� ��������� �����
        free(result->digits); // ����������� ������ ������
        result->digits = new_digits; // ��������� ��������� �� �����
        result->size = new_size; // ��������� ������ ����������
    }

    return result; // ���������� ���������
}



BigNumber* CopyBN(BigNumber* bn) {
    if (bn == NULL) {
        return NULL; // ���� ������� ��������� ����� NULL, ���������� NULL
    }

    // �������� ������ ��� ����� ��������� BigNumber
    BigNumber* copy = (BigNumber*)malloc(sizeof(BigNumber));
    if (copy == NULL) {
        return NULL; // ���� �� ������� �������� ������, ���������� NULL
    }

    // �������� ������ � ���� �� ������������ ��������� � �����
    copy->size = bn->size; // �������� ������ �����
    copy->is_negative = bn->is_negative; // �������� ���� �����

    // �������� ������ ��� ������� ���� � ����� ���������
    copy->digits = (digit*)calloc(copy->size, sizeof(digit));
    if (copy->digits == NULL) {
        free(copy); // ���� �� ������� �������� ������ ��� ������� ����, ����������� ������ ��� ��������� � ���������� NULL
        return NULL;
    }

    // �������� ������ ���� �� ������������ ��������� � �����
    memcpy(copy->digits, bn->digits, copy->size * sizeof(digit));

    return copy; // ���������� ��������� �� ����� ��������� BigNumber
}

BigNumber* MultiplyBN(BigNumber* bn1, BigNumber* bn2)
{
    // ���������, ��� ������� ��������� �� ����� NULL
    if (bn1 == NULL || bn2 == NULL)
        return NULL;

    // ��������, ���� ���� �� ����� ����� ����
    if ((bn1->size == 1 && bn1->digits[0] == 0) || (bn2->size == 1 && bn2->digits[0] == 0)) {
        // ������� ������ BigNumber ��� ����������
        BigNumber* zero_result = CreateBN("0");

        // ������������� ���� ����������
        zero_result->is_negative = false;

        return zero_result;
    }

    // ���������� ���� ����������
    bool is_negative = bn1->is_negative != bn2->is_negative;

    // �������� ������ ��� ����������
    size_t result_size = bn1->size + bn2->size;
    BigNumber* result = (BigNumber*)malloc(sizeof(BigNumber));
    if (result == NULL)
        return NULL;

    // �������� ������ ��� ������ ���� ����������
    result->digits = (digit*)calloc(result_size, sizeof(digit));
    if (result->digits == NULL)
    {
        free(result);
        return NULL;
    }
    result->size = result_size;
    result->is_negative = is_negative;

    // �������� ����� "���������"
    for (int i = bn1->size - 1; i >= 0; --i)
    {
        int carry = 0;
        for (int j = bn2->size - 1; j >= 0; --j)
        {
            // �������� ����� �� bn1 � bn2, �������� ������� ������ ���������� � �������
            int product = bn1->digits[i] * bn2->digits[j] + result->digits[i + j + 1] + carry;
            result->digits[i + j + 1] = product % 10;
            carry = product / 10;
        }
        result->digits[i] += carry; // ��������� ���������� ������� � �������� �������
    }

    // ������� ������� ���� �� ����������
    size_t non_zero_index = 0;
    while (non_zero_index < result_size && result->digits[non_zero_index] == 0)
        non_zero_index++;

    // ���� ��� ����� �������, ������������� ������ ���������� � 1 � �������� ������ 0
    if (non_zero_index == result_size)
    {
        result->size = 1;
        result->digits[0] = 0;
    }
    else
    {
        // ������� ����� ������ ��� �������� �������� ����
        result->size -= non_zero_index;
        memmove(result->digits, result->digits + non_zero_index, result->size);
    }

    return result;
}


BigNumber* MultiplyBNOnli(BigNumber* bn, int num)
{
    if (bn == NULL)
    {
        return NULL; // ���� ������� ��������� ����� NULL, ���������� NULL
    }

    // ���������� ���� ���������� ���������
    // ���� ����� bn � num �����������, ��������� �������������
    bool is_negative = (bn->is_negative && num > 0) || (!bn->is_negative && num < 0);

    // �������� num � ���������������� �������� ��� ��������� ��������
    num = abs(num);

    // ���� num ����� 0, ����������� ��������� �������� 0
    if (num == 0)
    {
        char zero[] = "0";
        return CreateBN(zero); // ������� BigNumber, �������������� 0, � ���������� ���
    }

    int carry = 0; // ���������� ��� �������� ��� ���������
    size_t result_size = bn->size + 1; // ������ ���������� ��������� �� ������� ������, ��� � ��������� �����
    BigNumber* result = (BigNumber*)malloc(sizeof(BigNumber)); // �������� ������ ��� ����������
    if (result == NULL)
    {
        return NULL; // ���� �� ������� �������� ������, ���������� NULL
    }

    // �������� ������ ��� ������� ���� � ���������� � �������������� ��� ������
    result->digits = (digit*)calloc(result_size, sizeof(digit));
    if (result->digits == NULL)
    {
        free(result); // ���� �� ������� �������� ������ ��� ������� ����, ����������� ������ ��� ��������� � ���������� NULL
        return NULL;
    }
    result->size = result_size; // ������������� ������ ����������
    result->is_negative = is_negative; // ������������� ���� ����������

    // ��������� ��������� ���������, ������� � ������� ����
    for (int i = bn->size - 1; i >= 0; --i)
    {
        // �������� ������� ����� �� num � ��������� �������
        int product = bn->digits[i] * num + carry;
        result->digits[i + 1] = product % 10; // ������� �� ������� �� 10 - ������� ����� ����������
        carry = product / 10; // ������� ��� ��������� ��������
    }

    result->digits[0] = carry; // ������� ���������� ������� ������ ����������

    // ������� ������� ����, ���� ��� ����
    if (result->digits[0] == 0)
    {
        // �������� ��� ����� �� ���� ������� �����
        memmove(result->digits, result->digits + 1, result_size - 1);
        result->size--; // ��������� ������ ���������� �� 1
    }

    return result; // ���������� ��������� �� ���������
}


int CompareBN(BigNumber* bn1, BigNumber* bn2)
{
    // ���� ���� �� ����� NULL, �������, ��� ��� ������
    if (bn1 == NULL && bn2 == NULL)
        return 0; // ��� ����� �����, ���������� 0
    else if (bn1 == NULL)
        return -1; // ����� bn1 �����������, �������, ��� bn2 ������, ���������� -1
    else if (bn2 == NULL)
        return 1; // ����� bn2 �����������, �������, ��� bn1 ������, ���������� 1

    // �������� �� ��������� ������
    if (bn1->is_negative && !bn2->is_negative)
        return -1; // bn1 �������������, bn2 �������������, ������� bn1 ������, ���������� -1
    else if (!bn1->is_negative && bn2->is_negative)
        return 1; // bn1 �������������, bn2 �������������, ������� bn1 ������, ���������� 1

    // ��������� �� ������
    if (bn1->size > bn2->size)
        return bn1->is_negative ? -1 : 1; // ������ bn1 ������, ������� bn1 ������, ���� �������������, � ������, ���� �������������
    else if (bn1->size < bn2->size)
        return bn1->is_negative ? 1 : -1; // ������ bn2 ������, ������� bn1 ������, ���� �������������, � ������, ���� �������������

    // ������� �����, ������������ ���������
    for (size_t i = 0; i < bn1->size; ++i)
    {
        if (bn1->digits[i] > bn2->digits[i])
            return bn1->is_negative ? -1 : 1; // ����� � bn1 ������, ������� bn1 ������, ���� �������������, � ������, ���� �������������
        else if (bn1->digits[i] < bn2->digits[i])
            return bn1->is_negative ? 1 : -1; // ����� � bn2 ������, ������� bn1 ������, ���� �������������, � ������, ���� �������������
    }

    // ����� �����
    return 0; // ��� ����� �����, ���������� 0
}


BigNumber* MinusreversBN(BigNumber* bn1, BigNumber* bn2)
{
    // ���������, ��� ������� ��������� �� ����� NULL
    if (bn1 == NULL || bn2 == NULL)
        return NULL;

    // ���������� ������������ ������ ����������
    size_t max_size = (bn1->size > bn2->size) ? bn1->size : bn2->size;

    // �������� ������ ��� ����������
    BigNumber* result = (BigNumber*)malloc(sizeof(BigNumber));
    if (result == NULL)
        return NULL;

    // �������� ������ ��� ������ ���� ����������
    result->digits = (digit*)calloc(max_size, sizeof(digit));
    if (result->digits == NULL)
    {
        free(result);
        return NULL;
    }
    result->size = max_size;

    // ���� ����� ������ ������, ��������� ��������
    if (bn1->is_negative != bn2->is_negative)
    {
        // �������� ���� ������� ����� � ��������� ��������
        bn2->is_negative = !bn2->is_negative;
        result = SumBN(bn1, bn2);
        bn2->is_negative = !bn2->is_negative; // ���������� ���� ������� �����
    }
    else // ���� ����� ������ �����, ��������� ���������
    {
        bool swap = false;

        // ���������, ����� ����� �� ������ ������
        if (bn1->size < bn2->size || (bn1->size == bn2->size && memcmp(bn1->digits, bn2->digits, bn1->size) < 0))
        {
            // ������ ������� ����� � ��������, ��� ����������� �����
            BigNumber* temp = bn1;
            bn1 = bn2;
            bn2 = temp;
            swap = true;
        }

        int borrow = 0;
        for (size_t i = 0; i < max_size; ++i)
        {
            // �������� ����� �� ����� bn1 � bn2, �������� ������������ �� ��������
            int digit1 = (i < bn1->size) ? bn1->digits[bn1->size - 1 - i] : 0;
            int digit2 = (i < bn2->size) ? bn2->digits[bn2->size - 1 - i] : 0;

            // �������� ����� � ������ �����
            int diff = digit1 - digit2 - borrow;

            // ���� �������� �������������, ��������� 10 � ������������� ����
            if (diff < 0)
            {
                diff += 10;
                borrow = 1;
            }
            else
            {
                borrow = 0;
            }

            // ���������� �������� � ��������������� ������ ����������
            result->digits[max_size - 1 - i] = diff;
        }

        // ������������� ���� ���������� � ����������� �� ����� ������
        result->is_negative = swap;

        // ������� ������� ���� �� ����������
        size_t non_zero_index = 0;
        while (non_zero_index < result->size && result->digits[non_zero_index] == 0)
            non_zero_index++;

        // ���� ��� ����� �������, ������������� ������ ���������� � 1 � �������� ������ 0
        if (non_zero_index == result->size)
        {
            result->size = 1;
            result->digits[0] = 0;
        }
        else
        {
            // ������� ����� ������ ��� �������� �������� ����
            size_t new_size = result->size - non_zero_index;
            digit* new_digits = (digit*)calloc(new_size, sizeof(digit));

            // �������� �������� ����� � ����� ������
            for (size_t i = 0; i < new_size; ++i)
                new_digits[i] = result->digits[non_zero_index + i];

            // ����������� ������ ������ � ������������� ����� ������ � ������ � ���������
            free(result->digits);
            result->digits = new_digits;
            result->size = new_size;
        }
    }

    // ���������� ��������� ���������
    return result;
}


BigNumber* DivideBN(BigNumber* dividend, BigNumber* divisor)
{
    // �������� ������� ������
    if (dividend == NULL || divisor == NULL || divisor->size == 0 || (divisor->size == 1 && divisor->digits[0] == 0))
        return NULL;

    // �������� �� ������� �� ���� ��� ������� ����
    if ((divisor->size == 1 && divisor->digits[0] == 0) || (dividend->size == 1 && dividend->digits[0] == 0))
    {
        BigNumber* zero = CreateBN("0"); // �������� ������� BigNumber ��� ����� 0
        return zero; // ���������� ��������� �� ������, �������������� ����� 0
    }

    // �������� ����� �����, ����� �������� � �� ����������� ����������
    BigNumber* abs_dividend = CopyBN(dividend); // �������� ����� ��������
    BigNumber* abs_divisor = CopyBN(divisor);   // �������� ����� ��������
    if (abs_dividend == NULL || abs_divisor == NULL)
    {
        DeleteBN(&abs_dividend); // ������������ ������, ���� �������� ����� �� �������
        DeleteBN(&abs_divisor);  // ������������ ������, ���� �������� ����� �� �������
        return NULL;
    }
    abs_dividend->is_negative = false; // ��������� ����� ����� �������� ��� �������������
    abs_divisor->is_negative = false;  // ��������� ����� ����� �������� ��� �������������

    // �������� ������� ���������� �������
    BigNumber* quotient = CreateBN("0"); // �������� ������� BigNumber ��� �������� ���������� �������
    if (quotient == NULL)
    {
        DeleteBN(&abs_dividend); // ������������ ������, ���� �������� ���������� �� �������
        DeleteBN(&abs_divisor);  // ������������ ������, ���� �������� ���������� �� �������
        return NULL;
    }

    // �������� ����� �������� ��� ������������� � ����� �������
    BigNumber* remainder = CopyBN(abs_dividend); // �������� ����� �������� ��� ������������� � ����� �������
    if (remainder == NULL)
    {
        DeleteBN(&quotient);      // ������������ ������, ���� �������� ����� �������� �� �������
        DeleteBN(&abs_dividend);  // ������������ ������, ���� �������� ����� �������� �� �������
        DeleteBN(&abs_divisor);   // ������������ ������, ���� �������� ����� �������� �� �������
        return NULL;
    }

    // �������� �� ��������� ���� ��������
    if (CompareBN(abs_dividend, CreateBN("0")) == 0)
    {
        DeleteBN(&abs_divisor); // ������������ ������, ���� ������� ����� ����
        return quotient;        // ���������� ������� ���������
    }

    // �������� �� ��������� �������� ��������
    if (CompareBN(abs_divisor, abs_dividend) == 0)
    {
        DeleteBN(&abs_divisor);  // ������������ ������, ���� �������� ����� ��������
        DeleteBN(&remainder);    // ������������ ������, ���� �������� ����� ��������
        quotient->digits[0] = 1; // ������������� ������� � ���������� �������
        return quotient;         // ���������� ��������� �������
    }

    // ��������, ��� �������� ������ ��������
    if (CompareBN(abs_divisor, abs_dividend) > 0)
    {
        DeleteBN(&abs_divisor); // ������������ ������, ���� �������� ������ ��������
        DeleteBN(&remainder);   // ������������ ������, ���� �������� ������ ��������
        return quotient;        // ���������� ������� ���������
    }

    // ���� ������� ������ ��� ����� ��������, ���������� �������
    while (CompareBN(remainder, abs_divisor) >= 0)
    {
        // ������������� �������� ��� �������� ���������� ���������
        int count = 0;

        // �������� �������� �� ������� ������� ���, ���� ������� ������ ��� ����� ��������
        while (CompareBN(remainder, abs_divisor) >= 0)
        {
            // �������� �������� �� �������
            BigNumber* subtracted = MinusreversBN(remainder, abs_divisor); // ��������� �������� �� �������
            DeleteBN(&remainder); // ����������� ������, ���������� ��� ���������� �������
            remainder = subtracted; // ��
            // ����������� �������
            count++;
        }

        // ����������� ���������� ��������� � "�����" ���������� ������� � ��������� �� � ����������
        char count_str[12]; // ������������ ����� ����� - 10 ��������
        sprintf(count_str, "%d", count); // ����������� ���������� ��������� � ������
        BigNumber* count_bn = CreateBN(count_str); // ������� BigNumber ��� �������� ���������� ���������
        BigNumber* temp_quotient = MultiplyBNOnli(quotient, 10); // �������� ������� ��������� ������� �� 10
        BigNumber* new_quotient = SumBN(temp_quotient, count_bn); // ��������� ����� � ���������� �������
        DeleteBN(&count_bn); // ����������� ������, ���������� ��� ������ count_bn
        DeleteBN(&temp_quotient); // ����������� ������, ���������� ��� ������ temp_quotient
        DeleteBN(&quotient); // ����������� ������, ���������� ��� ���������� ��������� �������
        quotient = new_quotient; // ��������� ��������� �������
    }

    // ����������� ������, ���������� �������� � ��������� ���������
    DeleteBN(&remainder); // ����������� ������, ���������� ��� �������
    DeleteBN(&abs_divisor); // ����������� ������, ���������� ��� ��������
    DeleteBN(&abs_dividend); // ����������� ������, ���������� ��� �������

    return quotient; // ���������� ��������� �������
}
